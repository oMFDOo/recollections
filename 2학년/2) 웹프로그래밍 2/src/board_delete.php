<?php

    $num   = $_GET["num"];
    $page   = $_GET["page"];

    $con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
    $sql = "select * from board where num = $num";
    $result = mysqli_query($con, $sql);
    $row = mysqli_fetch_array($result);

    $copied_name = $row["file_copied"];

     // 글 작성으로 받은 포인트 회수
     $point_up = 100;
     session_start();
     if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
     else $userid = "";

     $sql2 = "select point from members where id='$userid'";
     $result = mysqli_query($con, $sql2);
     $row = mysqli_fetch_array($result);
     $new_point = $row["point"] - $point_up;
     $_SESSION['userpoint'] = $new_point;	// 포인트 세션 등록
     
     $sql2 = "update members set point=$new_point where id='$userid'";
     mysqli_query($con, $sql2);


     if ($copied_name) {
       $file_path = "./data/".$copied_name;
       unlink($file_path);
     }

     $sql = "delete from board where num = $num";
     mysqli_query($con, $sql);
     mysqli_close($con);

     echo "
       <script>
           location.href = 'board_list.php?page=$page';
       </script>
     ";
?>

