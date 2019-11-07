import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import { useFormik } from 'formik';
import Box from '@material-ui/core/Box';
import text from '../ELCP01.txt';
import { getLookup } from '../script';
import CryptoJS from 'crypto-js';

const checkIfUserPasswordInDictionary = async password => {
  let passwordIsPresent = false;
  await fetch(text)
    .then(result => result.text())
    .then(resText => {
      const passwordArray1 = resText.split('\n');
      passwordIsPresent = passwordArray1.includes(password);
    })
  return passwordIsPresent;
}

const Password = () => {
  const [passwordPresent, setPasswordPresent] = useState(null);
  const [elcp02, setelcp02] = useState([]);

  useEffect(() => {
    setelcp02(localStorage.getItem('password array'));
  }, []);

  const formik = useFormik({
    initialValues: {
      password: '',
    },
    onSubmit: values => {
      const { password } = values;
      const passwordArray2 = JSON.parse(elcp02);
      checkIfUserPasswordInDictionary(password)
        .then(present => {
          if (present) setPasswordPresent('The entered password is subject to a dictionary attack.');
          else if (passwordArray2.includes(password)) {
            const message = getLookup(passwordArray2, password);
            setPasswordPresent(`The entered password is subject to a targeted attack because it is related to ${message}.`)
          }
          else {
            const saltedPassword = password + localStorage.getItem('salt');
            const hashedPasswordArray = CryptoJS.SHA1(saltedPassword).words;
            let hashedPassword = ''
            hashedPasswordArray.forEach(item => {
              hashedPassword += item.toString();
            })
            localStorage.setItem('password', hashedPassword);
            setPasswordPresent('Account Created')
          }
        });
    }
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
            <p>{passwordPresent}</p> :
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
    width: '40%'
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
