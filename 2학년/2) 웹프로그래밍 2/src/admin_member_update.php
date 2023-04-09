<?php
    session_start();
    if (isset($_SESSION["userlevel"])) $userlevel = $_SESSION["userlevel"];
    else $userlevel = "";

    if ( $userlevel != 1 )
    {
        echo("
            <script>
            alert('관리자가 아닙니다! 회원정보 수정은 관리자만 가능합니다!');
            history.go(-1)
            </script>
        ");
        exit;
    }

    $num   = $_GET["num"];
    $level = $_POST["level"];
    $point = $_POST["point"];
    

    $con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
    $sql = "update members set level=$level, point=$point where num=$num";

    // 로그인 계정의 포인트 변경시
    // if($_SESSION["userid"] == $row["id"]){
    //     $_SESSION['userpoint'] = $point;	
    // }

    mysqli_query($con, $sql);

    mysqli_close($con);

    echo "
	     <script>
	         location.href = 'admin.php';
	     </script>
	   ";
?>

