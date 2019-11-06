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
	userInfo += obj.firstName;
	userInfo += "";
	
	userInfo += obj.lastName;
	userInfo += "";
	
    var dTemp = obj.dob.split("/");
    userInfo += dTemp[0];
    userInfo += dTemp[1];
    userInfo += dTemp[2];
    userInfo += dTemp[2].substring(2);
	userInfo += "";
	
	userInfo += obj.phone.substring(0, 3);
	userInfo += obj.phone.substring(3, 6);
	userInfo += obj.phone.substring(6);
	userInfo += "";
	
	var aTemp = obj.street.split();
	for (var i = 0; i < aTemp.size; ++i) {
		userInfo += aTemp[i];
	}
	userInfo += obj.apt;
	userInfo += obj.city;
	userInfo += obj.state;
	userInfo += obj.zip;
	userInfo += "";
	
	var re = /[._]/;
	var eTemp = obj.email.split("@")[0].split(re);
	for (var j = 0; j < eTemp.size; ++j) {
		userInfo += eTemp[j];
	}
	
	return userInfo;
}

function finalECLP2(obj) {
	var finalPW = basicELCP2(obj);
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
    return finalPW;
}