<div align="center">
    <img src="./img/main_img.png" style="width: 1080px">
</div>
        <div align="center">
            <table>
                <th style="padding: 0px 10px 0px 10px;"><img src="./img/prize1.png" style="width: 250px"></th>
                <th style="padding: 0px 10px 0px 10px;"><img src="./img/prize2.png" style="width: 250px"></th>
                <th style="padding: 0px 10px 0px 10px;"><img src="./img/prize3.png" style="width: 250px"></th>
                <th style="padding: 0px 10px 0px 10px;"><img src="./img/prize4.png" style="width: 250px"></th>
            </table>
        </div>
        <div id="main_content">
            <div id="latest">
                <h4 style="font-size: 20px;">최근 게시글</h4>
                <ul>
<!-- 최근 게시 글 DB에서 불러오기 -->
<?php
    $con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
    $sql = "select * from board order by num desc limit 5";
    $result = mysqli_query($con, $sql);

    if (!$result)
        echo "게시판 DB 테이블(board)이 생성 전이거나 아직 게시글이 없습니다!";
    else
    {
        while( $row = mysqli_fetch_array($result) )
        {
            $regist_day = substr($row["regist_day"], 0, 10);
            if(mb_strlen($row["subject"], "UTF-8") > 17) {
                $subject = mb_substr($row["subject"], 0, 17, "UTF-8");
                $subject .= "...";
            }
            else {
                $subject = $row["subject"];
            }

?> 
                
                <li style="font-size: 17px;">
                    <span><a href="board_view.php?num=<?=$row["num"]?>&page=<?=$row["page"]?>" style="color: #fff"><?=$subject?></a></span>
                    <span><?=$row["name"]?></span>
                    <span><?=$regist_day?></span>
                </li>   
<?php
        }
    }
?>
            </div>
            <div id="point_rank">
                <h4  style="font-size: 20px;">포인트 랭킹</h4>
                <ul>
<!-- 포인트 랭킹 표시하기 -->
<?php
    $rank = 1;
    $sql = "select * from members order by point desc limit 5";
    $result = mysqli_query($con, $sql);

    if (!$result)
        echo "회원 DB 테이블(members)이 생성 전이거나 아직 가입된 회원이 없습니다!";
    else
    {
        while( $row = mysqli_fetch_array($result) )
        {
            $name  = $row["name"];        
            $id    = $row["id"];
            $point = $row["point"];
            $name = mb_substr($name, 0, 1)." * ".mb_substr($name, 2, 1);
?>
                <li style="font-size: 17px;">
                    <span><?=$rank?></span>
                    <span><?=$name?></span>
                    <span><?=$id?></span>
                    <span><?=$point?></span>
                </li>
<?php
            $rank++;
        }
    }

    mysqli_close($con);
?>
                </ul>
            </div>
        </div>