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
    // GET RFID PARAMETER
    $rfid = $_GET["rfid"];
    // echo $rfid;

    $sql = "SELECT * FROM `student` WHERE `rfid` = :rfid";
    $stmt = $conn->prepare($sql);
    $stmt->execute([":rfid" => $rfid]);
    $result = $stmt->fetch();
    $stmt->closeCursor();

    http_response_code(200);
    echo json_encode($result);
}
