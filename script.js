var testObj = {
      firstName: 'Cole',
      lastName: 'Buhman',
      dob: '03/01/1998',
      phone: '8017661234',
      street: '945 X Bird Lane',
      apt: '709',
      city: 'Logan',
      state: 'Utah',
      zip: '84040',
      email: 'buhman_cole.den@gmail.com'
}

var lookup = ["first name", "last name", "date of birth", "phone number", "address", "email"];

function basicELCP2(obj) {
	// initial list
	var userInfo = [];
    
	userInfo.push(obj.firstName);
	userInfo.push("");
	
	userInfo.push(obj.lastName);
	userInfo.push("");
	
    var dTemp = obj.dob.split("/");
    userInfo.push(dTemp[0]);
    userInfo.push(dTemp[1]);
    userInfo.push(dTemp[2]);
    userInfo.push(dTemp[2].substring(2));
	userInfo.push("");
	
	userInfo.push(obj.phone.substring(0, 3));
	userInfo.push(obj.phone.substring(3, 6));
	userInfo.push(obj.phone.substring(6));
	userInfo.push("");
	
	var aTemp = obj.street.split(" ");
	for (var i = 0; i < aTemp.length; ++i) {
		if (aTemp[i].length > 1)
            userInfo.push(aTemp[i]);
	}
	userInfo.push(obj.apt);
	userInfo.push(obj.city);
	userInfo.push(obj.state);
	userInfo.push(obj.zip);
	userInfo.push("");
	
	var re = /[._]/;
	var eTemp = obj.email.split("@")[0].split(re);
	for (var j = 0; j < eTemp.length; ++j) {
		userInfo.push(eTemp[j]);
	}
	
	return userInfo;
}

function finalECLP2(obj) {
	var finalPW = basicELCP2(obj);
	var rplc = ["a@", "b8", "c(", "d6", "e3", "g9", "h#", "i1", "i!", "k<", "l1", "l|", "o0", "q9", "s5", "s$", "t7", "t+", "v<", "v>", "x%", "y?"];//, "s$", "s5"];
	for (var i = 0; i < rplc.length; ++i) {
		for (var j = 0; j < finalPW.length; ++j) {
			for (var k = 0; k < finalPW[j].length; ++k) {
				if (finalPW[j].charAt(k) == rplc[i].charAt(0)) {
					finalPW.splice(j+1, 0, finalPW[j].replace(rplc[i].charAt(0), rplc[i].charAt(1)));
				}
			}
		}
	}
    return finalPW;
}