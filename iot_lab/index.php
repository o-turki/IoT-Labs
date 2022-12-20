<?php

date_default_timezone_set("Africa/Tunis");

require __DIR__ . "./src/config/Database.php";
require __DIR__ . "./src/controllers/StudentController.php";

// JSON HEADERS
header("Access-Control-Allow-Origin: *");
header("Content-type: application/json; charset=UTF-8");


// SPLIT URI(/URL) BY / INTO PARTS (LIST)
// echo $_SERVER["REQUEST_URI"];
$parts = explode("/", $_SERVER["REQUEST_URI"]);
// print_r($parts);

// EXAMPLE:     http://192.168.1.56/iot_lab/api/v1/student/
//              => $resource = student

$resource = $parts[4] ?? null;
// echo $resource;


// INITIALIZE DB
$db = new Database("127.0.0.1", "iot_lab", "root", "");


// INITIALIZE MODELS
$student = new Student($db);


// INITIALIZE CONTROLLERS
$studentController = new StudentController($student);


// ROUTING
switch ($resource) {
    case "student":
        $studentController->processRequest();
        break;
}
