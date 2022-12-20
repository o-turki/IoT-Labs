<?php

require __DIR__ . "./../models/Student.php";


class StudentController
{
    public function __construct(private Student $student)
    {
    }

    public function processRequest()
    {
        $method = $_SERVER["REQUEST_METHOD"];

        switch ($method) {
            case "GET":
                $this->getStudent();
                break;
        }
    }

    private function getStudent()
    {
        // GET RFID PARAMETER
        // http://192.168.1.56/iot_lab/api/v1/student/?rfid=331d3090
        $rfid = $_GET["rfid"];
        // echo $rfid;

        echo json_encode($this->student->getStudentByRFID($rfid));
    }
}
