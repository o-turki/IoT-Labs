<?php

date_default_timezone_set("Africa/Tunis");

// JSON's HEADERS
header("Access-Control-Allow-Origin: *");
header("Content-type: application/json; charset=UTF-8");


// TRY TO CONNECT TO THE DATABASE
try {
    $hostname = "127.0.0.1";
    $db_name = "iot_lab";
    $username = "root";
    $password = "";

    $dsn = "mysql:host=$hostname;dbname=$db_name;charset=utf8mb4";
    $options = [
        PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC
    ];

    $conn = new PDO($dsn, $username, $password, $options);
} catch (PDOException $e) {
    // HTTP 500: Internal server error
    http_response_code(500);

    echo json_encode([
        "error" => "Connection failed",
        "message" => $e->getMessage()
    ]);
    exit();
}


// EXAMPLE: http://192.168.1.56/iot_lab/?rfid=12345678
$method = $_SERVER["REQUEST_METHOD"];

if ($method == "GET") {
    // GET 'rfid PARAMETER
    $rfid = $_GET["rfid"];
    // echo $rfid;

    $sql = "SELECT * FROM `student` WHERE `rfid` = :rfid;";
    $stmt = $conn->prepare($sql);
    $stmt->execute([":rfid" => $rfid]);
    $result = $stmt->fetch();
    $stmt->closeCursor();

    if (!$result) {  // $result = false
        http_response_code(404);

        $empty = json_decode("{}");
        echo json_encode($empty); // "{}"
        exit();
    }

    echo json_encode($result);
} else if ($method == "POST") {
    $data = (array) json_decode(file_get_contents("php://input"), true);

    $firstName = $data["first_name"];
    $lastName = $data["last_name"];
    $currentDay = date("d/m/Y");
    $currentTime = date("H:i:s");

    $sql = "INSERT INTO `presence`
                (`first_name`, `last_name`, `cur_day`, `cur_time`)
            VALUES
                (:first_name, :last_name, :cur_day, :cur_time);";
    $stmt = $conn->prepare($sql);
    $stmt->execute([
        ":first_name" => $firstName,
        ":last_name" => $lastName,
        ":cur_day" => $currentDay,
        ":cur_time" => $currentTime
    ]);
    $stmt->closeCursor();

    http_response_code(201);
    echo json_encode(["message" => "Presence Inserted"]);
}
