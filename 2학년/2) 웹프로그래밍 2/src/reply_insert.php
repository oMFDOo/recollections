<?php

//url에 action이라는 값이 존재하면
if(isset($_POST["action"]))
{   //db연결
    $connect = mysqli_connect("localhost", "Jinju", "", "member");
    //url에 action이라는 값이 "추가" 라면
    if($_POST["action"]=="추가")
    {       //ajax로 넘긴 data를 받아준다.
            $board_id=mysqli_real_escape_string($connect,$_POST["board_id"]);
            $parent_id=mysqli_real_escape_string($connect,$_POST["parent_id"]);
            $depth=mysqli_real_escape_string($connect,$_POST["depth"]);
            $reply_writer=mysqli_real_escape_string($connect,$_POST["reply_writer"]);
            $reply_content=mysqli_real_escape_string($connect,$_POST["reply_content"]);
            
            //참고-mysqli_real_escape_string
            //:MySQL로 질의를 전송하기 전에 안전하게 데이터를 만들기 위해 사용
            //특수 문자열을 이스케이프하여 mysql_query() 수행시 안전하게 질의할 수 있도록 한다.

            //insert 프로시저 생성
            $procedure = "
                CREATE PROCEDURE insertReply(IN board_id int, parent_id int, depth int, reply_writer text, reply_content text)
                BEGIN
                INSERT INTO users(board_id, parent_id, depth, reply_writer, reply_content) VALUES(board_id, parent_id, depth, reply_writer, reply_content);
                END
            ";

            //위에서 만든 프로시저 실행
            if(mysqli_query($connect,$procedure))
            {   
                $query = "CALL insertReply('".$board_id ."','".$parent_id."','".$depth."','".$reply_writer."','".$reply_content."')";
                //프로시저 호출
                mysqli_query($connect,$query);
                echo '성공적으로 입력 되었습니다.';
            }
    }

}
?>