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
      <h1>This is the login form</h1>
      <p>Create Account stuff</p>
      <li><Link to='/form'>Create Account To Take you to a form</Link></li>
      <Box
        display="flex"
        border={1}
        flexDirection='column'
        alignItems='center'
      >
        <form
          onSubmit={formik.handleSubmit}
          style={{ display: 'flex', flexDirection:'column', justifyContent: 'center', alignItems: 'center' }}
        >
          <label htmlFor="userName">UserName</label>
          <input
            id="userName"
            name="userName"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.userName}
          />
          <label htmlFor="password">Password</label>
          <input
            id="password"
            name="password"
            type="password"
            onChange={formik.handleChange}
            value={formik.values.password}
          />
          <button type="submit">Submit</button>
        </form>
      </Box>
    </div>
  );
}

export default App;
