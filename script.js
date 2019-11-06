// class for user info in task 2
var formObj = {};

function initValidation(formName) {
    window.addEventListener("load", function() {
        var form = document.querySelector(formName);
        form.addEventListener("submit", function(event) {
            if (form.checkValidity() == false) {
                event.preventDefault();
                event.stopPropagation();
            }
            form.classList.add("was-validated");
            
            formObj.fname = document.getElementById("fname").value;
            formObj.lname = document.getElementById("lname").value;
            formObj.address = document.getElementById("address").value;
            formObj.city = document.getElementById("city").value;
            formObj.state = document.getElementById("state").value;
            formObj.zip = document.getElementById("zip").value;
            formObj.phone = document.getElementById("phone").value;
            formObj.email = document.getElementById("email").value;
            formObj.uname = document.getElementById("username").value;
            formObj.pword = document.getElementById("password").value;
            formObj.origin = [];
            formObj.comment = document.getElementById("comments").value;
            
            var checks = document.getElementsByName("origin");
            for (var i in checks) {
                if (checks[i].checked)
                    formObj.origin.push(checks[i].value);
            }
            var radios = document.getElementsByName("rating");
            for (var j in radios) {
                if (radios[j].checked)
                    formObj.rating = radios[i].value;
            }
            
            window.alert("Thanks!\nHere are your Results:\n" + JSON.stringify(formObj, null, 4));
        });
    }, false);
}

var lookup = ["first name", "last name", "date of birth", "phone number", "address", "email"];

function basicELCP2() {
	// initial list
	var userInfo = [];
	userInfo += obj.fname;
	userInfo += "";
	
	userInfo += obj.lname;
	userInfo += "";
	
	userInfo += obj.dob; // need to know how it's stored to grab year/etc
	userInfo += "";
	
	userInfo += obj.phone;
	userInfo += obj.phone.substring(0, 3);
	userInfo += obj.phone.substring(3, 6);
	userInfo += obj.phone.substring(6);
	userInfo += "";
	
	var aTemp = obj.address.split();
	for (var i = 0; i < aTemp.size; ++i) {
		userInfo += aTemp[i];
	}
	userInfo += obj.apt;
	userInfo += obj.city;
	userInfo += obj.state;
	userInfo += obj.zip;
	userInfo += "";
	
	var re = /[._\s]/;
	var eTemp = obj.email.split("@")[0].split(re);
	for (var i = 0; i < eTemp.size; ++i) {
		userInfo += eTemp[i];
	}
	
	return userInfo;
}

function finalECLP2() {
	var finalPW = basicELCP2();
	var replacements = ["a@", "i!", "s$", "s5"];
	for (var i = 0; i < replacements.size; ++i) {
		for (var j = 0; j < finalPW.size; ++j) {
			for (var k = 0; k < finalPW[j].size; ++k) {
				if (finalPW[j].charAt(k) == replacements[i].charAt(0)) {
					finalPW.splice(j+1, 0, finalPW[j].splice(k, 1, replacements[i].charAt(1)));
				}
			}
		}
	}
}

function validateForm() {
    var $x = $("input[required]")
    $x.each(function() {
        checkRequired($(this).attr("id"), "Required");
    });
    checkFormat("zip", "Wrong Format", /^$|^[0-9]{5}$/);
    checkFormat("phone", "Wrong Format", /^[0-9]{3}-?[0-9]{3}-?[0-9]{4}$/);
    checkFormat("email", "Wrong Format", /^[a-zA-Z0-9_.-]+@[a-z0-9-]+\.[a-z.-]+$/);
    checkFormat("password", "Wrong Format", /^(?=.*[A-Z])([a-zA-Z0-9_]{8,})/);
    checkButtons("origin", "Required");
    checkButtons("rating", "Required");
}

function checkRequired(fieldName, message) {
    var field = document.getElementById(fieldName);
    if (field.value.length > 0) {
        field.setCustomValidity("");
        if (field.parentElement.querySelector("p")) // rm error message
            $(field.parentElement.lastChild).remove();
    } else {
        field.setCustomValidity(message);
        if (!field.parentElement.querySelector("p")) // add error message
            $(field).after("<p style='margin:0; padding:5px; color:red;'>" + message + "</p>");
    }
    
    formValidated();
    return field.value.length > 0 ? true : false;
}

function checkFormat(fieldName, message, re) {
    var field = document.getElementById(fieldName);
    if (field.value.match(re)) {
        field.setCustomValidity("");
        if (field.parentElement.querySelector("p")) // rm error message
            $(field.parentElement.lastChild).remove();
    }
    else {
        field.setCustomValidity(message);
        if (!field.parentElement.querySelector("p")) // add error message
            $(field).after("<p style='margin:0; padding:5px; color:red;'>" + message + "</p>");
    }
    
    formValidated();
    return field.value.match(re) ? true : false;
}

function formValidated() {
    var form = document.querySelector(".needs-validation");
    form.classList.add('was-validated');
}

//var $form = $("#form");
var password;
function definePassword() {
	password = $("#form ul li input#password").val();
	console.log(password);
}
