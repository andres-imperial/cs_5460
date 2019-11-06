//password creation
//password validation to check against the lists
//if match is found, do a bad thing, make a stronger password
//else create the account


//storing the password
//generate a salt
//concatenate salt to password
//compute hash digest on whole concatenated salt/password
//store the hash in a password storage file
//store salt in separate file

import React from 'react';
import { Link } from 'react-router-dom';
import { useFormik } from 'formik';
import Box from '@material-ui/core/Box';
import text from '../ELCP01.txt';

const checkIfUserPasswordInDictionary = async ({ password }) => {
  let passwordIsPresent = false;
  fetch(text)
    .then(result => result.text())
    .then(resText => {
      const passwordArray = resText.split('\n')
      passwordIsPresent = passwordArray.includes(password);
      console.log(passwordIsPresent)
    })
  return passwordIsPresent;
}

const Password = () => {
  const formik = useFormik({
    initialValues: {
      password: '',
    },
    onSubmit: values => {
      //alert(JSON.stringify(values, null, 2));
      checkIfUserPasswordInDictionary(values)
    },
  });
  return (
    <div>
      <h1>Password</h1>
      <li><Link to='/'>Takes you back to login page</Link></li>
      <Box
        display="flex"
        border={1}
        flexDirection='column'
        alignItems='center'
      >
        <form
          onSubmit={formik.handleSubmit}
          style={{ display: 'flex', flexDirection: 'column', justifyContent: 'center', alignItems: 'center' }}
        >
          <label htmlFor="password">Password</label>
          <input
            id="password"
            name="password"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.password}
          />
          <button type="submit">Submit</button>
        </form>
      </Box>
    </div>
  )
}

export default Password;
