import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import Box from '@material-ui/core/Box';
import { useFormik } from 'formik';
import CryptoJS from 'crypto-js';
import Modal from 'react-modal';

const App = () => {
  const [loginMessage, setLoginMessage] = useState(null);
  const [badLoginAttempts, setBadLoginAttempts] = useState(0);
  const [showModal, setShowModal] = useState(false);

  useEffect(() => {
    const tempSalt = CryptoJS.lib.WordArray.random(4);
    const salt = tempSalt.words[0].toString();
    if (localStorage.getItem('salt') == null) {
      localStorage.setItem('salt', salt);
    }
  }, [])

  const formik = useFormik({
    initialValues: {
      userName: '',
      password: '',
    },
    onSubmit: values => {
      const saltedPassword = values.password + localStorage.getItem('salt');
      const hashedPasswordArray = CryptoJS.SHA1(saltedPassword).words;
      let hashedPassword = ''
      hashedPasswordArray.forEach(item => {
        hashedPassword += item.toString();
      })
      if (hashedPassword === localStorage.getItem('password')) {
        setLoginMessage('Successful Login');
      } else {
        setLoginMessage('Error Logging In');
        setBadLoginAttempts(badLoginAttempts + 1);
        console.log(badLoginAttempts);
        //after 3 times lockout for 2^0 minutes
        //after 3 more times lockout for 2^1 minutes
        //on successful login reset back to 2^0 minutes
      }
    }
  });

  return (
    <div>
      <h1 style={{ padding: 10 }}>Login</h1>
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
            <label style={styles.label} htmlFor='userName'>UserName:</label>
            <input
              id='userName'
              name='userName'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.userName}
            />
          </div>
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
        <p>Don't have an account?
          <li style={{ listStyleType: 'none' }}>
            <Link to='/form'>Create Account</Link>
          </li>
        </p>
        {
          loginMessage ?
            <p>{loginMessage}</p> :
            null
        }
      </Box>
      <ReactModal
        isOpen={showModal}
        contentLabel="Minimal Modal Example"
      >
        {/* <button onClick={setShowModal(false)}>Close Modal</button> */}
      </ReactModal>
    </div>
  );
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

export default App;
