<?php
    session_start();
    if (isset($_SESSION["userlevel"])) $userlevel = $_SESSION["userlevel"];
    else $userlevel = "";

    if ( $userlevel != 1 )
    {
        echo("
            <script>
            alert('�����ڰ� �ƴմϴ�! ȸ������ ������ �����ڸ� �����մϴ�!');
            history.go(-1)
            </script>
        ");
        exit;
    }

    $num   = $_GET["num"];
    $title = $_POST["title"];
    $link = $_POST["link"];
    

    $con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
    $sql = "update notice set title='$title', link='$link' where num=$num";

    mysqli_query($con, $sql);

    mysqli_close($con);

    echo "
	     <script>
	         location.href = 'admin.php';
	     </script>
	   ";
?>

