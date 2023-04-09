<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>내 맘 속의 미키마우섭</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/admin.css">
</head>
<body bgcolor="#444" style="color: #fff">
<header>
    <?php include "header.php";?>
</header>  
<section>

	<!--공지 관리-->
	<div id="admin_box">
	    <h3 id="member_title">
	    	관리자 모드 > 공지 관리
		</h3>
	    <ul id="notice_list"style="color: #000">
				<li>
					<span class="col1">번호</span>
					<span class="col2">제목</span>
					<span class="col3">링크</span>
					<span class="col4">수정</span>
				</li>
<?php
	if (isset($_SESSION["userlevel"]) == false || $_SESSION["userlevel"] != 1)
	{
		echo("<script>
				alert('올바른 접근이 아닙니다.');
				history.go(-1);
				</script>
			");
		exit;
	}
?>
<?php
	$con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
	$sql = "select * from notice order by num asc";
	$result = mysqli_query($con, $sql);
	$total_record = mysqli_num_rows($result); // 전체 회원 수

	$number = 1;

   while ($row = mysqli_fetch_array($result))
   {
      $num         = $row["num"];
	  $title       = $row["title"];
	  $link        = $row["link"];
?>
			
		<li>
		<form method="post" action="admin_notice_update.php?num=<?=$num?>" style="color: #fff">
			<span class="col1"><?=$number?></span>
			<span class="col2"><input type="text" name="title" value="<?=$title?>"></span>
			<span class="col3"><input type="text" name="link" value="<?=$link?>"></span>
			<span class="col4"><button type="submit">수정</button></span>
		</form>
		</li>	
			
<?php
   	   $number++;
   }
?>
		</ul>
		

    <!--회원 관리-->
   	<div id="admin_box">
	    <h3 id="member_title">
	    	관리자 모드 > 회원 관리
		</h3>
	    <ul id="member_list"style="color: #000">
				<li>
					<span class="col1">번호</span>
					<span class="col2">아이디</span>
					<span class="col3">이름</span>
					<span class="col4">레벨</span>
					<span class="col5">포인트</span>
					<span class="col6">가입일</span>
					<span class="col7">수정</span>
					<span class="col8">삭제</span>
				</li>
<?php
	$con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
	$sql = "select * from members order by point desc";	// 포인트 순으로 정렬
	$result = mysqli_query($con, $sql);
	$total_record = mysqli_num_rows($result); // 전체 회원 수

	$number = 1;

   while ($row = mysqli_fetch_array($result))
   {
      $num         = $row["num"];
	  $id          = $row["id"];
	  $name        = $row["name"];
	  $level       = $row["level"];
      $point       = $row["point"];
      $regist_day  = $row["regist_day"];
?>
			
		<li>
		<form method="post" action="admin_member_update.php?num=<?=$num?>" style="color: #fff">
			<span class="col1"><?=$number?></span>
			<span class="col2"><?=$id?></a></span>
			<span class="col3"><?=$name?></span>
			<span class="col4"><input type="text" name="level" value="<?=$level?>"></span>
			<span class="col5"><input type="text" name="point" value="<?=$point?>"></span>
			<span class="col6"><?=$regist_day?></span>
			<span class="col7"><button type="submit">수정</button></span>
			<span class="col8"><button type="button" onclick="location.href='admin_member_delete.php?num=<?=$num?>'">삭제</button></span>
		</form>
		</li>	
			
<?php
   	   $number++;
   }
?>
		</ul>


		<!--게시판 관리-->
	    <h3 id="member_title">
	    	관리자 모드 > 게시판 관리
		</h3>
	    <ul id="board_list">
		<li class="title" style="color: #000">
			<span class="col1">선택</span>
			<span class="col2">번호</span>
			<span class="col3">이름</span>
			<span class="col4">제목</span>
			<span class="col5">첨부파일명</span>
			<span class="col6">작성일</span>
		</li>
		<form method="post" action="admin_board_delete.php">
<?php
	$sql = "select * from board order by num desc";
	$result = mysqli_query($con, $sql);
	$total_record = mysqli_num_rows($result); // 전체 글의 수

	$number = $total_record;

   while ($row = mysqli_fetch_array($result))
   {
      $num         = $row["num"];
	  $name        = $row["name"];
	  $subject     = $row["subject"];
	  $file_name   = $row["file_name"];
      $regist_day  = $row["regist_day"];
      $regist_day  = substr($regist_day, 0, 10)
?>
		<li>
			<span class="col1"><input type="checkbox" name="item[]" value="<?=$num?>"></span>
			<span class="col2"><?=$number?></span>
			<span class="col3"><?=$name?></span>
			<span class="col4"><?=$subject?></span>
			<span class="col5"><?=$file_name?></span>
			<span class="col6"><?=$regist_day?></span>
		</li>	
<?php
   	   $number--;
   }
   mysqli_close($con);
?>
				<button type="submit">선택된 글 삭제</button>
			</form>
	    </ul>
	</div> <!-- admin_box -->
</section> 
<footer>
    <?php include "footer.php";?>
</footer>
</body>
</html>
