import React from 'react';
import { Link } from 'react-router-dom';
import Box from '@material-ui/core/Box';
import { useFormik } from 'formik';

const App = () => {

  //page with form to enter in info
  //page to create password
  //page to login

  //user enters in username and password **Done**
  //check to see if password entered concatenated with salt and hashed
  //  matches stored hash
  //if they enter in the password incorrectly, they can have 3 failed login attempts
  //after which they are locked out for 2^0 minutes
  //3 more times 
  //2^1
  //etc.
  //after successful attempt reset number of lockouts to 0

  const formik = useFormik({
    initialValues: {
      userName: '',
      password: '',
    },
    onSubmit: values => {
      alert(JSON.stringify(values, null, 2));
    },
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
              type='password'
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

      </Box>
    </div>
  );
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

export default App;
