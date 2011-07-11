<?php

/**
 * @file
 * Admin functions for httpbl.
 */

/**
 * Implementation of hook_admin_settings()
 *
 *** Configuration settings for httpBL
 */

function httpbl_admin_settings($form, &$form_state) {
  if (!$_POST && (!variable_get('httpbl_accesskey', NULL) || !variable_get('httpbl_check', HTTPBL_CHECK_NONE))) {
    drupal_set_message(t('Blacklist lookups are currently disabled; enter your access key below and enable checks to enable blacklist lookups.'), 'error');
  }

  $form['core'] = array(
    '#type' => 'fieldset',
    '#title' => t('Http:BL'),
    '#description' => t('Http:BL implements a malicious traffic blocker using http:BL by Project Honey Pot.<br />To use this capability you will need an http:BL access key, received from Project Honey Pot.  For more information about http:BL, see the <a href="http://www.projecthoneypot.org/httpbl.php">http:BL homepage at projecthoneypot.org</a>.'),
    '#collapsible' => TRUE,
  );

  $form['core']['httpbl_accesskey'] = array(
    '#type' => 'textfield',
    '#title' => t('http:BL Access Key'),
    '#default_value' => variable_get('httpbl_accesskey', NULL),
    '#description' => t('Your http:BL <a href="http://www.projecthoneypot.org/faq.php#g">Access Key</a>.'),
    '#size' => 20,
    '#maxlength' => 12,
  );

  $form['core']['httpbl_check'] = array(
    '#type' => 'radios',
    '#title' => t('Http:BL checks'),
    '#default_value' => variable_get('httpbl_check', HTTPBL_CHECK_NONE),
    '#options' => array(
      t('Disabled'),
      t('On comment submissions'),
      t('On all page requests'),
    ),
    '#description' => t('Determines when host/ip blacklist checking should occur.'),
  );

  $form['honeypot'] = array(
    '#type' => 'fieldset',
    '#title' => t('Honeypot'),
    '#description' => t('Your Honeypot (spam trap) settings. For more information, see the <a href="http://www.projecthoneypot.org/">Project Honey Pot homepage</a>.'),
    '#collapsible' => TRUE,
  );

  $form['honeypot']['httpbl_footer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add link to footer'),
    '#default_value' => variable_get('httpbl_footer', FALSE),
    '#description' => t('Whether to add your honeypot link to the footer of every page.'),
  );

  $form['honeypot']['httpbl_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Honeypot link'),
    '#default_value' => variable_get('httpbl_link', NULL),
    '#description' => t('Your Honeypot (spam trap) link. This can be one of your <a href="http://www.projecthoneypot.org/manage_honey_pots.php">own Honey Pots</a> or a <a href="http://www.projecthoneypot.org/manage_quicklink.php">QuickLink</a>.'),
  );

  $form['honeypot']['httpbl_word'] = array(
    '#type' => 'textfield',
    '#title' => t('Link word'),
    '#default_value' => variable_get('httpbl_word', 'randomness'),
    '#description' => t('A random word which will be used as a link.'),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logs, Stats and Cache Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced']['httpbl_log'] = array(
    '#type' => 'radios',
    '#title' => t('Http:BL logging'),
    '#default_value' => variable_get('httpbl_log', HTTPBL_LOG_MIN),
    '#options' => array(
      t('Off - (some errors only)'),
      t('Log all positive lookups in the watchdog.'),
      t('Verbose logging (useful for testing and learning how this works).'),
    ),
    '#description' => t('Whether to enable logging and how much (verbose logging not recommended when checking all request.'),
  );

  $form['advanced']['httpbl_stats'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable statistics'),
    '#default_value' => variable_get('httpbl_stats', TRUE),
    '#description' => t('Whether to enable counting of positive lookups. Statistics are show on the Drupal <a href="@statusreport">Status report page</a>.', array('@statusreport' => url('admin/reports/status'))),
    );
  
  $form['advanced']['httpbl_cache'] = array(
    '#type' => 'radios',
    '#title' => t('Results Caching'),
    '#default_value' => variable_get('httpbl_cache', HTTPBL_CACHE_DB),
    '#options' => array(
      t('Off'),
      t('Http:BL cache'),
      t('Http:BL cache and Drupal blocked_ips table'),
    ),
    '#description' => t('Whether to enable database-based caching. Note that when this is disabled, IPs that fail the session whitelist test cannot be automatically banned. The Drupal Blocked_ips table allows visitors to be banned in the early stages of the bootstrap.'),
  );

  $cache_period = drupal_map_assoc(array(10800, 21600, 32400, 43200, 86400, 172800, 259200, 604800, 1209600, 2419200), 'format_interval');
  $form['advanced']['httpbl_safe_offset'] = array(
    '#type' => 'select', 
    '#title' => t('Safe Visitor Cache Expires in...'), 
    '#default_value' => variable_get('httpbl_safe_offset', 10800), 
    '#options' => $cache_period, 
    '#description' => t('How long to keep safe or white-listed IPs in cache.'),
  );

  $cache_period2 = drupal_map_assoc(array(43200, 86400, 172800, 259200, 604800, 1209600, 1814400, 2419200), 'format_interval');
  $form['advanced']['httpbl_greylist_offset'] = array(
    '#type' => 'select', 
    '#title' => t('Grey Listed Visitor Cache Expires in...'), 
    '#default_value' => variable_get('httpbl_greylist_offset', 86400), 
    '#options' => $cache_period2, 
    '#description' => t('How long to keep grey-listed IPs in cache.'),
  );

  $cache_period3 = drupal_map_assoc(array(604800, 1209600, 1814400, 2419200, 7257600, 15724800, 31536000, 63072000, 94608000), 'format_interval');
  $form['advanced']['httpbl_blacklist_offset'] = array(
    '#type' => 'select', 
    '#title' => t('Black Listed Visitor Cache Expires in...'), 
    '#default_value' => variable_get('httpbl_blacklist_offset', 31536000), 
    '#options' => $cache_period3, 
    '#description' => t('How long to keep black-listed IPs in cache (and also blocked in Drupal Blocked_ips table, when applicable).'),
  );

  return system_settings_form($form);
}

/**
 * Form API callback to validate the httpbl settings form.
 */
function httpbl_admin_settings_validate($form, &$form_state) {
  $key = $form_state['values']['httpbl_accesskey'];
 

  if ($form_state['values']['httpbl_check'] && !$key) {
    form_set_error('httpbl_accesskey', t('You must enter an access key to enable blacklist checks.'));
  }

  if ($form_state['values']['httpbl_footer'] && !$form_state['values']['httpbl_link']) {
    form_set_error('httpbl_link', t('You must enter a link to be able to add it to the footer.'));
  }

  if ($key) {
    // Key should be 12 lowercase alpha characters.
    // There's no unicode allowed, so we're not using drupal_strlen().
    // ereg is deprecated.  Now using preg_grep instead?
    if (preg_grep('/[^a-z]/', array($key)) || strlen($key) != 12) {
      form_set_error('httpbl_accesskey', t('Your access key is formatted incorrectly.'));
    }
    else if (!count(form_get_errors())) {
      // Do a test lookup (with known result).
      // Not sure we are really testing a valid key?
      $lookup = httpbl_dnslookup('127.1.80.1', $key);
      if (!$lookup || $lookup['threat'] != 80) {
        form_set_error('httpbl_accesskey', t('Testcase failed. This either means that your access key is incorrect or that there is a problem in your DNS system.'));
      }
      else {
        drupal_set_message('Http:BL test completed successfully.');
      }
    }
  }

}