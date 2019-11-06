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
      
    },
  });

  return (
    <div>
      <h1>Form</h1>
      <li><Link to='/password'>Go to page to create password</Link></li>
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
          <label htmlFor="firstName">First Name</label>
          <input
            id="firstName"
            name="firstName"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.firstName}
          />
          <label htmlFor="lastName">Last Name</label>
          <input
            id="lastName"
            name="lastName"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.lastName}
          />
          <label htmlFor="dob">Date Of Birth</label>
          <input
            id="dob"
            name="dob"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.dob}
          />
          <label htmlFor="phone">Phone Number</label>
          <input
            id="phone"
            name="phone"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.phone}
          />
          <label htmlFor="street">Street Information</label>
          <input
            id="street"
            name="street"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.street}
          />
          <label htmlFor="apt">Apartment Number</label>
          <input
            id="apt"
            name="apt"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.apt}
          />
          <label htmlFor="city">City</label>
          <input
            id="city"
            name="city"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.city}
          />
          <label htmlFor="state">State</label>
          <input
            id="state"
            name="state"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.state}
          />
          <label htmlFor="zip">Zip Code</label>
          <input
            id="zip"
            name="zip"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.zip}
          />
          <label htmlFor="email">Email Address</label>
          <input
            id="email"
            name="email"
            type="text"
            onChange={formik.handleChange}
            value={formik.values.email}
          />
          <button type="submit">Submit</button>
        </form>
      </Box>
    </div>
  )
}

export default Form;
