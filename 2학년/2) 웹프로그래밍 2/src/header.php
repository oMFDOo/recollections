<style>
    .circle{
        display:inline;
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

<?php
    session_start();
    if (isset($_SESSION["userid"])) $userid = $_SESSION["userid"];
    else $userid = "";
    if (isset($_SESSION["username"])) $username = $_SESSION["username"];
    else $username = "";
    if (isset($_SESSION["userlevel"])) $userlevel = $_SESSION["userlevel"];
    else $userlevel = "";
    if (isset($_SESSION["userpoint"])) $userpoint = $_SESSION["userpoint"];
    else $userpoint = "";
?>		
        <div id="">
            
            <ul id="">
            
<?php
    if(!$userid) {
?>                
                <li id="header_set"><a href="member_form.php"style="color: #fff">회원 가입</a> | <a href="login_form.php"style="color: #fff">로그인</a></li>
<?php
    } else {
                $logged = $username."(".$userid.")님[Level:".$userlevel.", Point:".$userpoint."]";
?>
                <li li id="header_set">
                    <?=$logged?> | <a href="logout.php"style="color: #fff">로그아웃</a> | 
                    <a href="member_modify_form.php"style="color: #fff">나의 정보 확인</a>
<?php
    }
?>
<?php
    if($userlevel==1) {
?>
                 | <a href="admin.php"style="color: #fff">관리자 모드</a></li>
<?php
    }
?>

<?php
    // session_start();
    $print = "";
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
                <div class="circle" style="color: #F56; width: 50px; padding: 2px 5px 2px 5px;"> $notRead </div>
            PRINT;
        }
        mysqli_close($con);
    }
?>

            </ul>
        </div>
        <div id="menu_bar"style="color: #fff">
            <table border="0">
                <th><a href="index.php"><img src="./img/main_logo.png" style="width: 160px"></a></th>
                <th><a href="index.php" class="title wave"><span>HOME</span></a></th>
                <th><a href="board_list.php" class="title wave"><span>우리들의 덕질</span></a></th>
                <th><a href="board_form.php" class="title wave"><span>주접글 작성</span></a></th>
                <th><a href="video_gallery.php" class="title wave"><span>강의 정주행~!</span></a></th>
                <th><a href="image_gallery.php" class="title wave"><span>교수님 갤러리</span></a></th>
                <th><a href="message_form.php" class="title wave"><span>사랑의 메신저<?php echo "$print"?></span></a></th>
                
            </table>
        </div>
        <?php
            $con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
            $sql = "select * from notice";
            $result = mysqli_query($con, $sql);
            $total_record = mysqli_num_rows($result);

            $count = 0;
            $link_list = array();
            $title_list = array();
            for ($i=0; $i<$total_record; $i++)
            {
                mysqli_data_seek($result, $i);
                // 가져올 레코드로 위치(포인터) 이동
                $row = mysqli_fetch_array($result);
                // 하나의 레코드 가져오기
                $title_list[$count] = $row["title"];
                $link_list[$count++] = $row["link"];
            }
        ?>
        <div style="margin-bottom: 50px;">
            <div class="animated-text">
                <?php
                    for($i = 0; $i < $total_record; $i++) {
                        $str = <<<LINK
                        <div class="line"><a href="$link_list[$i]" style="color: #ff9c2a;">[공지] <span style="color:#fff;">$title_list[$i]</span></a></div>           
                        LINK;
                        echo $str;
                    }
                ?>
            </div>
        </div>
        