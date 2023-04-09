<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>PHP 프로그래밍 입문</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/board.css">
</head>
<body bgcolor="#444" style="color: #fff">
<header>
    <?php include "header.php";?>
</header>
<section>
   	<div id="board_box">
	    <h3 class="title">
			게시판 > <a style="color: #30d5ff;"> 내용보기 </a>
		</h3>
<?php
	$num  = $_GET["num"];
	$page  = $_GET["page"];

	$con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
	$sql = "select * from board where num=$num";
	$result = mysqli_query($con, $sql);

	$row = mysqli_fetch_array($result);
	$id      = $row["id"];
	$name      = $row["name"];
	$regist_day = $row["regist_day"];
	$subject    = $row["subject"];
	$content    = $row["content"];
	$file_name    = $row["file_name"];
	$file_type    = $row["file_type"];
	$file_copied  = $row["file_copied"];
	$hit          = $row["hit"];

	// $content = str_replace(" ", "&nbsp;", $content);
	$content = str_replace("\n", "<br>", $content);

	$new_hit = $hit + 1;
	$sql = "update board set hit=$new_hit where num=$num";
	mysqli_query($con, $sql);
?>
	    <ul id="view_content">
			<li>
				<span class="col1"><b>제목 :</b> <?=$subject?></span>
				<span class="col2"><?=$name?> | <?=$regist_day?></span>
			</li>
			<li>
				<?php
					if($file_name) {
						$real_name = $file_copied;
						$file_path = "./data/".$real_name;
						$file_size = filesize($file_path);

						echo "▷ 첨부파일 : $file_name ($file_size Byte) &nbsp;&nbsp;&nbsp;&nbsp;
			       		<a style='color: #12cffa' href='download.php?num=$num&real_name=$real_name&file_name=$file_name&file_type=$file_type'>[저장]</a><br><br>";
			           	}
				?>
				<?php
					$content = str_replace("&lt;", "<", $content);
					$content = str_replace("&quot;", '"', $content);
					$content = str_replace("&gt;", ">", $content);
					echo $content;
				?>
			</li>
		</ul>


		<?php
			// 로그인 계정과 글 작성자가 동일한 경우에만 수정 가능
			if ((isset($_SESSION["userid"]) && (isset($_SESSION["userlevel"]))) && (($id == $_SESSION["userid"]) || (1 == $_SESSION["userlevel"]))) {
				include ("board_view_button1.html");
			}
			else {
				include ("board_view_button2.html");
			}
		?>


	</div> <!-- board_box -->
</section>
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>
