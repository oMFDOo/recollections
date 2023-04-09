<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>내 맘 속의 미키마우섭</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/main.css">
</head>
<style>
    .container {
        display: flex;
        flex-wrap: nowrap;
        margin-left: 7px;
        flex-direction: row;
        justify-content: center;
    }
    .container-item {
        display: flex;
        flex-wrap: wrap;
        margin-left: 7px;
        flex-direction: column;
    }
    .video {
        margin-bottom: 20px;
    }
    td {
        text-align: center;
    }

    .btn {
        display: inline-block;
        padding: 6px 12px;
        margin-bottom: 0;
        font-size: 14px;
        font-weight: normal;
        line-height: 1.42857143;
        text-align: center;
        white-space: nowrap;
        vertical-align: middle;
        cursor: pointer;
        -webkit-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
                user-select: none;
        background-image: none;
        border: 1px solid transparent;
        border-radius: 4px;
    }
    
    .btn-lg {
        font-size: 18px;
        line-height: 1.33;
        border-radius: 6px;
    }

    .btn-primary {
        color: #fff;
        background-color: #e22f2f;
        border-color: #e22f2f;
    }

    .btn-primary:hover,
    .btn-primary:focus,
    .btn-primary:active,
    .btn-primary.active,
    .open .dropdown-toggle.btn-primary {
        color: #fff;
        background-color: #e22f2f;
        border-color: #e22f2f;
    }

    /***********************
    OUTLINE BUTTONS
    ************************/

    .btn.outline {
        background: none;
        padding: 12px 22px;
    }
    .btn-primary.outline {
        border: 2px solid #fff;
        color: #fff;
    }
    .btn-primary.outline:hover, .btn-primary.outline:focus, .btn-primary.outline:active, .btn-primary.outline.active, .open > .dropdown-toggle.btn-primary {
        color: #fff;
        background-color: #e22f2f;
        border-color: #e22f2f;
    }
    .btn-primary.outline:active, .btn-primary.outline.active {
        border-color: #fff;
        color: #fff;
        box-shadow: none;
    }

    /***********************
    CUSTON BTN VALUES
    ************************/

    .btn {
        padding: 14px 24px;
        border: 0 none;
        font-weight: 700;
        letter-spacing: 1px;
        text-transform: uppercase;
    }
    .btn:focus, .btn:active:focus, .btn.active:focus {
        outline: 0 none;
    }
</style>

<body bgcolor="#444" style="color: #fff"> 
	<header>
    	<?php include "header.php";?>
    </header>
    <div style="padding-top: 20px; padding-bottom: 20px;" align="center">
        <img src="./img/gallery1.png" style="width: 1080px">
    </div>
    <?php
        $con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
        $sql = "select * from video";
        $result = mysqli_query($con, $sql);
        $total_record = mysqli_num_rows($result);

        $count = 0;
    ?>
    <section>
	    <div class="container">
            <div class="container-item">
    
                <?php
                    $link_list = array();
                    $name_list = array();
                    for ($i=0; $i<$total_record; $i++)
                    {
                        mysqli_data_seek($result, $i);
                        // 가져올 레코드로 위치(포인터) 이동
                        $row = mysqli_fetch_array($result);
                        // 하나의 레코드 가져오기
                        $name         = $row["name"];
                        $link          = $row["link"];

                        $name_list[$count] = $name;
                        $link_list[$count++] = $link;
                    }
                ?>
                <div align="center">
                    <table border="1" width="1000px">
                        <th width="5%">번호</th>
                        <th width="75%">강의명</th>
                        <th width="20%">바로가기</th>
                        <?php
                            for($i = 0; $i < $total_record; $i++) {
                                $str = <<<LINK
                                <tr>
                                    <td>$i</td>
                                    <td>$name_list[$i]</td>
                                    <td><button onclick="location.href='$link_list[$i]' " type="button" class="btn btn-primary btn-lg outline">강의 보러가기</button></td>
                                </tr>            
                                LINK;
                                echo $str;
                            }
                        ?>
                    </table>
                </div>
                <div style="padding-top: 20px; padding-bottom: 20px;" align="center">
                    <img src="./img/grid.png" style="width: 1080px">
                </div>
            </div>
        </div>
</body>
<footer>
    <?php include "footer.php";?>
</footer>
</html>
