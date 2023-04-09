<!DOCTYPE html>
<html>

<style>
    .circle{
        width:20px;
        height:20px;
        border-radius:50%;
        color: #f56
        border-color: #fff;
        background-color:#fff;
        text-align:center;
        font-size:15px;
        font-weight: 900;
    }
</style>
<body bgcolor="#444" style="color: #fff">
<section style="color: #f56">
<?php
    // session_start();
    if(isset($_SESSION["userid"])) {
        $con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
        $userid = $_SESSION["userid"];
        $sql = "select * from message where rv_id='$userid' order by num desc";

        $result = mysqli_query($con, $sql);
        $total_record = mysqli_num_rows($result); // 전체 글 수
        
        $notRead = 0;
        for ($i=0; $i<$total_record; $i++)
        {
            mysqli_data_seek($result, $i);
            // 가져올 레코드로 위치(포인터) 이동
            $row = mysqli_fetch_array($result);
            // 하나의 레코드 가져오기
            $read    = $row["isRead"];

            if ($read == 0){
                $notRead++;
            }	  
        }
        if($notRead != 0){
            $print = <<<PRINT
                $notRead
            PRINT;
            echo $print;
        }
        mysqli_close($con);
    }
?>


</section>
</body>
</html>
