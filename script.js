// class for user info in task 2
var userInfo = {
  "fname": "",
  "address": {
    "street": "",
	"apt": "",
  }
  // ...
};

//var $form = $("#form");
var password;
function definePassword() {
	password = $("#form ul li input#password").val();
	console.log(password);
}