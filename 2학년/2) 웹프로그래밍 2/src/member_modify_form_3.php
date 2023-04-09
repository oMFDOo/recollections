<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>내 맘 속의 미키마우섭</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/message.css">
<link rel="stylesheet" type="text/css" href="https://netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css" rel="stylesheet">
<script type="text/javascript" src="./js/member_modify.js"></script>
<style>
@import url(//fonts.googleapis.com/earlyaccess/nanumgothic.css);
	.flex{
        display:flex;
        justify-content: center;
	}
	nav a {
		text-decoration:none;
		color:BLACK;
		font-size: 16px;
		display:block;
		border-bottom:1px solid #03A2A2;  
	}
	nav{
		margin-top:15px;
		margin-right: 80px;
		height:100%;
		width:250px;
		border-radius:5px;
	}
	.fa {
		position: relative;
		top:12px;
		width: 70px;
		height: 36px;
		text-align: center;
		font-size:20px;
	}
	nav span {
		position:relative;
		top:12px;
	}
	.logo{
		position:relative;
		top:0px;
		padding:1px;
		padding-top: 10px;
		padding-bottom: 5px;
		font-family: '나눔고딕';
		text-align:center;
		line-height: 0.8;
	}
</style>
</head>
<body bgcolor="#444" style="color: #fff"> 
<header>
    <?php include "header.php";?>
</header>  
<section style="color: #fff">
<section id="main_content" >
		<div class="flex">
		<nav style="padding-bottom: 165px;">
		<a style="color:#fff" class="logo" href="#">
			<h2>나의 정보 확인</h2>
			<p style="padding-bottom: 10px;">My Infomation</p>
		</a>

		<a style="color:#fff" href="member_modify_form_1.php">
			<i class="fa fa-user fa-lg"></i>
			<span>내 정보</span>
		</a>

		<a style="color:#fff" href="member_modify_form_2.php">
			<i class="fa fa-book fa-lg"></i>
			<span>내가 쓴 글</span>
		</a>
		
		<a style="color:#fff" href="member_modify_form_3.php">
			<i class="fa fa-envelope-o fa-lg"></i>
			<span>수신 쪽지함</span>
		</a>

		<a style="color:#fff" href="member_modify_form_4.php">
			<i class="fa fa-css3 fa-lg"></i>
			<span>송신 쪽지함</span>
		</a>
		</nav>
        <div id="message_box" style="margin:0 0;">
	    <h3>
<?php
 		if (isset($_GET["page"]))
			$page = $_GET["page"];
		else
			$page = 1;

		$mode = "post";

		if ($mode=="send")
			echo "송신 쪽지함 > 목록보기";
		else
            echo  "나의 정보 확인 > <a style='color: #30d5ff;'> 수신 쪽지함 </a>";
?>
		</h3>
	    <div>
	    	<ul id="message">
				<li>
					<span class="col1">번호</span>
					<span class="col2">제목</span>
					<span class="col3">
<?php						
						if ($mode=="send")
							echo "받은이";
						else
							echo "보낸이";
?>
					</span>
					<span class="col4">등록일</span>
				</li>
<?php
	$con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");

	if ($mode=="send")
		$sql = "select * from message where send_id='$userid' order by num desc";
	else
		$sql = "select * from message where rv_id='$userid' order by num desc";

	$result = mysqli_query($con, $sql);
	$total_record = mysqli_num_rows($result); // 전체 글 수

	$scale = 10;

	// 전체 페이지 수($total_page) 계산 
	if ($total_record % $scale == 0)     
		$total_page = floor($total_record/$scale);      
	else
		$total_page = floor($total_record/$scale) + 1; 
 
	// 표시할 페이지($page)에 따라 $start 계산  
	$start = ($page - 1) * $scale;      

	$number = $total_record - $start;

   for ($i=$start; $i<$start+$scale && $i < $total_record; $i++)
   {
      mysqli_data_seek($result, $i);
      // 가져올 레코드로 위치(포인터) 이동
      $row = mysqli_fetch_array($result);
      // 하나의 레코드 가져오기
	  $num    = $row["num"];
	  $subject     = $row["subject"];
      $regist_day  = $row["regist_day"];

	  if ($mode=="send")
	  	$msg_id = $row["rv_id"];
	  else
	  	$msg_id = $row["send_id"];
	  
	  $result2 = mysqli_query($con, "select name from members where id='$msg_id'");
	  $record = mysqli_fetch_array($result2);
	  $msg_name     = $record["name"];	  
?>
				<li style="color: #fff">
					<span class="col1"><?=$number?></span>
					<span class="col2"><a href="message_view.php?mode=<?=$mode?>&num=<?=$num?>"style="color: #fff"><?=$subject?></a></span>
					<span class="col3"><?=$msg_name?>(<?=$msg_id?>)</span>
					<span class="col4"><?=$regist_day?></span>
				</li>	
<?php
   	   $number--;
   }
   mysqli_close($con);
?>
	    	</ul>
			<ul id="page_num"> 	
<?php
	if ($total_page>=2 && $page >= 2)	
	{
		$new_page = $page-1;
		echo "<li><a href='message_box.php?mode=$mode&page=$new_page'>◀ 이전</a> </li>";
	}		
	else 
		echo "<li>&nbsp;</li>";

   	// 게시판 목록 하단에 페이지 링크 번호 출력
   	for ($i=1; $i<=$total_page; $i++)
   	{
		if ($page == $i)     // 현재 페이지 번호 링크 안함
		{
			echo "<li><b> $i </b></li>";
		}
		else
		{
			echo "<li> <a href='message_box.php?mode=$mode&page=$i'> $i </a> <li>";
		}
   	}
   	if ($total_page>=2 && $page != $total_page)		
   	{
		$new_page = $page+1;	
		echo "<li> <a href='message_box.php?mode=$mode&page=$new_page'>다음 ▶</a> </li>";
	}
	else 
		echo "<li>&nbsp;</li>";
?>
			</ul> <!-- page -->	    	
			<ul class="buttons">
				<li><button onclick="location.href='message_box.php?mode=rv'">수신 쪽지함</button></li>
				<li><button onclick="location.href='message_box.php?mode=send'">송신 쪽지함</button></li>
				<li><button onclick="location.href='message_form.php'">쪽지 보내기</button></li>
			</ul>
	</div> <!-- message_box -->
	</div> <!--사이드바-->
</section> 
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>
