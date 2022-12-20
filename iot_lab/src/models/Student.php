<?php


class Student
{
    private PDO $conn;

    public function __construct(Database $database)
    {
        $this->conn = $database->getConnection();
    }

    public function getStudentByRFID(string $rfid)
    {
        // echo $rfid;

        $sql = "SELECT * FROM `student` WHERE `rfid` = :rfid";
        $stmt = $this->conn->prepare($sql);
        $stmt->execute([":rfid" => $rfid]);
        $result = $stmt->fetch();
        $stmt->closeCursor();

        if (!$result) {
            http_response_code(400);
            return "{}";
        }

        return $result;
    }
}
