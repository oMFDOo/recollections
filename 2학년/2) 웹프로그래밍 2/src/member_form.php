<!DOCTYPE html>
<html>
<head> 
<meta charset="utf-8">
<title>내 맘 속의 미키마우섭</title>
<link rel="stylesheet" type="text/css" href="./css/common.css">
<link rel="stylesheet" type="text/css" href="./css/member.css">
<link rel="stylesheet" type="text/css" href="./css/bootstrap.min.css">
<link rel="stylesheet" type="text/css" href="./css/font-awesome.min.css">
<script src="./js/bootstrap.bundle.min.js"></script>
<script src="./js/jquery-3.3.1.slim.min.js"></script>

<style>
.login, .image {
  min-height: 100vh;
}
.container {
    display: flex;
    justify-content: center;
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
  padding: 10px 16px;
}
  
.btn-lg {
  font-size: 18px;
  line-height: 1.33;
  border-radius: 6px;
}

.btn-primary {
  color: #fff;
  background-color: #428bca;
  border-color: #357ebd;
}

.btn-primary:hover,
.btn-primary:focus,
.btn-primary:active,
.btn-primary.active,
.open .dropdown-toggle.btn-primary {
  color: #fff;
  background-color: #3276b1;
  border-color: #285e8e;
}

/***********************
  ROUND BUTTONS
************************/
.round {
  border-radius: 24px;
}

</style>
<script>
   function check_input()
   {
      if (!document.member_form.id.value) {
          alert("아이디를 입력하세요!");    
          document.member_form.id.focus();
          return;
      }

      if (!document.member_form.pass.value) {
          alert("비밀번호를 입력하세요!");    
          document.member_form.pass.focus();
          return;
      }

      if (!document.member_form.pass_confirm.value) {
          alert("비밀번호확인을 입력하세요!");    
          document.member_form.pass_confirm.focus();
          return;
      }

      if (!document.member_form.name.value) {
          alert("이름을 입력하세요!");    
          document.member_form.name.focus();
          return;
      }

      if (!document.member_form.email1.value) {
          alert("이메일 주소를 입력하세요!");    
          document.member_form.email1.focus();
          return;
      }

      if (!document.member_form.email2.value) {
          alert("이메일 주소를 입력하세요!");    
          document.member_form.email2.focus();
          return;
      }

      if (document.member_form.pass.value != 
            document.member_form.pass_confirm.value) {
          alert("비밀번호가 일치하지 않습니다.\n다시 입력해 주세요!");
          document.member_form.pass.focus();
          document.member_form.pass.select();
          return;
      }

      document.member_form.submit();
   }

   function reset_form() {
      document.member_form.id.value = "";  
      document.member_form.pass.value = "";
      document.member_form.pass_confirm.value = "";
      document.member_form.name.value = "";
      document.member_form.email1.value = "";
      document.member_form.id.focus();
      return;
   }

   function check_id() {
     window.open("member_check_id.php?id=" + document.member_form.id.value,
         "IDcheck",
          "left=700,top=300,width=350,height=200,scrollbars=no,resizable=yes");
   }
</script>
</head>
<body bgcolor="#444" style="color: #fff"> 
	<header>
    	<?php include "header.php";?>
    </header>
	<section>
        <!-- Demo content-->
        <div align="center">
            <div><h3 style="font-size: 40px; margin-top: 50px; font-weight: 100; color: #fff;">새로운 친구! 반가워!<br></h3></div>
            <div><p style="font-size: 15px; margin-bottom: 40px; font-weight: 100; color: #ffffffc9;">여긴 이현섭 교수님의 팬카페 미키마우섭이야.<br>너에 대해 알려줄래?</p></div>
            <div><img src="./img/sign_img.png" style="margin-bottom: 15px;"><div>
        </div>


        <div class="container" style="margin-bottom: 95px;">
            <div class="col-lg-8 col-xl-6 mx-auto">
                <form name="member_form" method="post" action="member_insert.php">
                    <div class="form-group mb-4">
                        <input id="inputEmail" type="text" name="id" placeholder="Id" style="width: 400px;" style="display: flex;" class="form-control rounded-pill border-0 shadow-sm px-4">
                        <button type="button" onclick="check_id()" class="btn btn-primary btn-lg round shadow-sm" style="font-weight: 600; font-size: 16px;">ID 중복체크</button>
                    </div>
                    <div class="form-group mb-4">
                        <input type="password" name="pass" placeholder="Password" class="form-control rounded-pill border-0 shadow-sm px-4 text-primary">
                    </div>
                    <div class="form-group mb-4">
                        <input type="password" name="pass_confirm" placeholder="Repeat Password" class="form-control rounded-pill border-0 shadow-sm px-4 text-primary">
                    </div>
                    <div class="form-group mb-4">
                        <input type="text" name="name" placeholder="Name" class="form-control rounded-pill border-0 shadow-sm px-4 text-primary">
                    </div>
                    <div class="form-group mb-5">
                        <input type="text" name="email1" placeholder="E-mail" class="form-control rounded-pill border-0 shadow-sm px-4 text-primary">
                    </div>
                    <button type="submit" onclick="check_input()" class="btn btn-primary btn-block text-uppercase mb-2 rounded-pill shadow-sm" style="font-weight: 600; font-size: 16px;">회원 가입</button>
                </form>
                <a href="#" onclick="reset_form()" style="color: #ddd; margin-left: 330px; font-size: 14px;">조금 더 둘러보고 올게요...^^</a>
            </div>
            
        </div><!-- End -->
	</section> 
	<footer>
    	<?php include "footer.php";?>
    </footer>
</body>
</html>

