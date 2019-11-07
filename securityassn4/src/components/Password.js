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

import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import { useFormik } from 'formik';
import Box from '@material-ui/core/Box';
import text from '../ELCP01.txt';

const checkIfUserPasswordInDictionary = async ({ password }) => {
  let passwordIsPresent = false;
  await fetch(text)
    .then(result => result.text())
    .then(resText => {
      const passwordArray = resText.split('\n')
      passwordIsPresent = passwordArray.includes(password);
    })
  return passwordIsPresent;
}

const Password = () => {
  const [passwordPresent, setPasswordPresent] = useState(false);
  const formik = useFormik({
    initialValues: {
      password: '',
    },

    onSubmit: values => {
      //alert(JSON.stringify(values, null, 2));
      checkIfUserPasswordInDictionary(values)
        .then(present => {
          if (present) setPasswordPresent(present);
          //else do account creation
        });
    },
  });

  return (
    <div>
      <h1>Password</h1>
      <li><Link to='/'>Takes you back to login page</Link></li>
      <Box
        display='flex'
        border={1}
        flexDirection='column'
        alignItems='center'
      >
        <form
          onSubmit={formik.handleSubmit}
          style={styles.form}
        >
          <div style={styles.input}>
            <label style={styles.label} htmlFor='password'>Password:</label>
            <input
              id='password'
              name='password'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.password}
            />
          </div>
          <button style={styles.button} type='submit'>Submit</button>
        </form>
        {
          passwordPresent ?
            <p>Error: This password is one that is commonly used or is based on your user info. Please try again to make a stronger password.</p> :
            null
        }
      </Box>
    </div>
  )
}

const styles = {
  form: {
    display: 'flex',
    flexDirection: 'column',
    width: '25%'
  },
  label: {},
  input: {
    padding: 2,
    display: 'flex',
    justifyContent: 'space-between',
  },
  button: {
    width: '50%',
    alignSelf: 'center'
  }
}

export default Password;
