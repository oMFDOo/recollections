<?php

//최종적으로 db에서 가져온 데이터를 가공한 결과 값을 담을 변수
$output = '';

//db연결 본인의 db 정보를 넣어준다!
$connect = mysqli_connect("localhost", "Jinju", "", "member");


//ajax로 넘긴 데이터 값은 "select"
//값이 존재하면 true를 리턴
if(isset($_POST["action"]))
{
    //users테이블 조회 프로시져를 만든다.
    $procedure = "
    CREATE PROCEDURE selectUser()
    BEGIN
    SELECT * FROM reply ORDER BY num DESC;
    END;
    ";

//mysqli_query:DB에 쿼리 전송
if(mysqli_query($connect,$procedure))
{
    $query = "CALL selectUser()";

    ///mysqli_query:DB에 쿼리 전송 후 결과값을 변수에 담는다
    $result = mysqli_query($connect,$query);
    $output .= '
    <table class="table table-bordered">
    <tr>
    <th width="35%">성</th>
    <th width="35%">이름</th>
    <th width="15%">수정</th>
    <th width="15%">삭제</th>
    </tr>

    ';
    //mysqli_num_rows 함수는 리절트 셋(result set)의 총 레코드 수를 반환한다.
    if(mysqli_num_rows($result) >0)
    {

        //mysqli_fetch_array 함수는 mysqli_query 를 통해 얻은 리절트 셋(result set)에서 레코드를 1개씩 리턴해주는 함수다.
        //레코드를 1개씩 리턴해주는 것은 mysqli_fetch_row 나 mysqli_fetch_assoc 와 동일하지만 리턴하는 배열의 형태가 틀리다.
        //mysqli_fetch_array 함수는 순번을 키로 하는 일반 배열과 컬럼명을 키로 하는 연관배열 둘 모두 값으로 갖는 배열을 리턴한다.
        //#참고!
        //mysqli_fetch_row 일반 배열(순번을 키로한다.)
        //mysqli_fetch_assoc 연관 배열
        //mysqli_fetch_array 일반 배열 + 연관배열(컬럼명을 키로 한다)

        //값이 있으면 true를 리턴한다.
        while($row = mysqli_fetch_array($result)){

            $output .= '
            <tr>
            <td>'.$row["first_name"].'</td>
            <td>'.$row["last_name"].'</td>
            <td><button type="button" name="update" id="'.$row["id"].'" class="update">수정</button></td>
            <td><button type="button" name="delete" id="'.$row["id"].'" class="delete">삭제</button></td>
            </tr>

            ';
        }
    }// 네번째 if문 끝
    else
    {
        $output .= '
        <tr>
        <td colspan="4">데이터가 없습니다.</td>
        </tr>
        ';
    }

    $output .= '</table>';

    //최종출력!
    echo $output;

}// 세번째 if문 끝

}//첫번째 if문 끝!





?>