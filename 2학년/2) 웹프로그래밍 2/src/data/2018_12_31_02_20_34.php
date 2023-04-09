<?php
    $id   = $_POST["id"];
    $pass = $_POST["pass"];
    $name = $_POST["name"];
    $email1  = $_POST["email1"];
    $email2  = $_POST["email2"];

    $email = $email1."@".$email2;
    $regist_day = date("Y-m-d (H:i)");  // 현재의 '년-월-일-시-분'을 저장

              
    $con = mysqli_connect("localhost", "user1", "12345", "sample");

    $sql = "select * from members where id='$id'";         // check redundant id
    $result = mysqli_query($con, $sql);
    $exist_id = mysqli_num_rows($result);

    if($exist_id) {
        echo("
            <script>
                window.alert('해당 아이디가 존재합니다.')
                history.go(-1)
            </script>
            ");
        exit;
    }

	$sql = "insert into members(id, pass, name, email, regist_day, level) ";
	$sql .= "values('$id', '$pass', '$name', '$email', '$regist_day', 9)";

	mysqli_query($con, $sql);  // $sql 에 저장된 명령 실행
    mysqli_close($con);     

    echo "
	      <script>
	          location.href = 'index.php';
	      </script>
	  ";
?>

   
