//pass values gathered to program that generates list of potential passwords

import React from 'react';
import { Link } from 'react-router-dom';
import Box from '@material-ui/core/Box';
import { useFormik } from 'formik';

const Form = () => {
  const formik = useFormik({
    initialValues: {
      firstName: '',
      lastName: '',
      dob: '',
      phone: '',
      street: '',
      apt: '',
      city: '',
      state: '',
      zip: '',
      email: ''
    },
    onSubmit: values => {
      // alert(JSON.stringify(values, null, 2));
      //check if certain values are not filled in, and alert to them
    },
  });

  return (
    <div>
      <h1>Form</h1>
      <li><Link to='/password'>Go to page to create password</Link></li>
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
            <label style={styles.label} htmlFor='firstName'>First Name:</label>
            <input
              id='firstName'
              name='firstName'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.firstName}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='lastName'>Last Name:</label>
            <input
              id='lastName'
              name='lastName'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.lastName}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='dob'>Date Of Birth:</label>
            <input
              id='dob'
              name='dob'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.dob}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='phone'>Phone Number:</label>
            <input
              id='phone'
              name='phone'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.phone}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='street'>Street Information:</label>
            <input
              id='street'
              name='street'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.street}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='apt'>Apartment Number:</label>
            <input
              id='apt'
              name='apt'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.apt}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='city'>City:</label>
            <input
              id='city'
              name='city'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.city}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='state'>State:</label>
            <input
              id='state'
              name='state'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.state}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='zip'>Zip Code:</label>
            <input
              id='zip'
              name='zip'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.zip}
            />
          </div>
          <div style={styles.input}>
            <label style={styles.label} htmlFor='email'>Email Address:</label>
            <input
              id='email'
              name='email'
              type='text'
              onChange={formik.handleChange}
              value={formik.values.email}
            />
          </div>
          <button style={styles.button} type='submit'>Submit</button>
        </form>
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

export default Form;
