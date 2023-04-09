<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>내 맘 속의 미키마우섭</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/member.css">
<link rel="stylesheet" type="text/css" href="https://netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css" rel="stylesheet">
<script type="text/javascript" src="./js/member_modify.js"></script>
<style>
@import url(//fonts.googleapis.com/earlyaccess/nanumgothic.css);
	.flex{
		display:flex;
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
	<?php    
		$con = mysqli_connect("localhost", "mfdo", "wlswn772##", "mfdo");
		$sql    = "select * from members where id='$userid'";
		$result = mysqli_query($con, $sql);
		$row    = mysqli_fetch_array($result);

		$pass = $row["pass"];
		$name = $row["name"];

		$email = explode("@", $row["email"]);
		$email1 = $email[0];
		$email2 = $email[1];

		mysqli_close($con);
	?>
	<!-- <div align="center">
        <img src="./img/main_img.png" style="width: 1080px">
    </div> -->
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
		<div style="color: #fff">
      		<div id="join_box">
          	<form name="member_form" method="post" action="member_modify.php?id=<?=$userid?>" style="font-family:Nanum Gothic;">
			    <p style="color: #30d5ff; font-size: xx-large; font-weight: bold; padding-bottom: 15px;">나의 정보<br></p>
				<h3 style="font-weight: 200; padding-bottom: 15px;">
					회원님께서 가입하신 내 맘속의 미키마우섭 정보입니다.<br>
					이현섭 교수님에 대한 팬심으로 아름다운 커뮤니티 활동을 이어나가 주세요.
				</h3>
				<hr>
    		    	<div class="form id">
				        <div class="col1">아이디</div>
				        <div class="col2">
							<?=$userid?>
				        </div>                 
			       	</div>
			       	<div class="clear"></div>

			       	<div class="form">
				        <div class="col1">비밀번호</div>
				        <div class="col2">
							<input type="password" name="pass" value="<?=$pass?>">
				        </div>                 
			       	</div>
			       	<div class="clear"></div>
			       	<div class="form">
				        <div class="col1">비밀번호 확인</div>
				        <div class="col2">
							<input type="password" name="pass_confirm" value="<?=$pass?>">
				        </div>                 
			       	</div>
			       	<div class="clear"></div>
			       	<div class="form">
				        <div class="col1">이름</div>
				        <div class="col2">
							<input type="text" name="name" value="<?=$name?>">
				        </div>                 
			       	</div>
			       	<div class="clear"></div>
			       	<div class="form email">
				        <div class="col1">이메일</div>
				        <div class="col2">
							<input type="text" name="email1" value="<?=$email1?>">@<input 
							       type="text" name="email2" value="<?=$email2?>">
				        </div>                 
			       	</div>
			       	<div class="clear"></div>
			       	<div class="bottom_line"> </div>
			       	<div class="buttons">
	                	<img style="cursor:pointer" src="./img/button_save.gif" onclick="check_input()">&nbsp;
                  		<img id="reset_button" style="cursor:pointer" src="./img/button_reset.gif"
                  			onclick="reset_form()">
	           		</div>
           	</form>
        	</div> <!-- join_box -->
        </div> <!-- main_content -->	
        
	</div> <!--사이드바-->
	</section> 
	<footer>
    	<?php include "footer.php";?>
    </footer>
</body>
</html>





