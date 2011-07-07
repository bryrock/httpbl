<?php

// httpbl.views_default.inc,v 1.0 2009/09/11 14:25:00 bryrock 

/**
 * @file
 * Default Views for http:BL for Drupal. Provides easy monitoring
 * of IPs greylisted or blacklisted through http:BL and linking to honeypot
 * to review why these IPs have been blocked.
 *
 * For this includes only
 * @author Bryan Lewellen (bryrock)
 * @link http://drupal.org/project/httpbl
 * @link http://httpbl.org/
 *
 * For http:BL for Drupal module
 * @author Mark Janssen (praseodym)
 * @link http://drupal.org/project/httpbl
 * @link http://httpbl.org/
 */

/**
 *
 * Version 6.x-dev
 * Contact: bryrock (at) raindearmedia (dot) com
 *
 * Feel free to improve this module, but please contact the authors with any
 * changes you make so they can be implemented into the 'official' version.
 *
 */

/**
 * Default Blocked Hosts Report (View)
 */
 
function httpbl_views_default_views() {
  // Thanks to Lullabot's clear and concise API docs at
  // http://api.lullabot.com/group/views_hooks
  //
  // Begin copy and paste of output from the Export tab of a view.
	$view = new view;
	$view->name = 'honeypot_blocked_httpbl';
	$view->description = 'Blocked Visitors via Honeypot.org.  This requires caching to be enabled at admin >> settings >> httpbl.';
	$view->tag = 'default';
	$view->view_php = '';
	$view->base_table = 'httpbl';
	$view->is_cacheable = FALSE;
	$view->api_version = 2;
	$view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
	$handler = $view->new_display('default', 'Defaults', 'default');
	$handler->override_option('fields', array(
	  'nothing' => array(
	    'label' => '',
	    'alter' => array(
	      'text' => 'Blocked via Honeypot
		--------------------------------------------------------------',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'exclude' => 0,
	    'id' => 'nothing',
	    'table' => 'views',
	    'field' => 'nothing',
	    'relationship' => 'none',
	  ),
	  'hostname' => array(
	    'label' => 'Hostname',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 1,
	      'path' => 'http://www.projecthoneypot.org/search_ip.php?ip=[hostname]',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'exclude' => 0,
	    'id' => 'hostname',
	    'table' => 'httpbl',
	    'field' => 'hostname',
	    'relationship' => 'none',
	  ),
	  'status' => array(
	    'label' => 'Status',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'set_precision' => FALSE,
	    'precision' => 0,
	    'decimal' => '.',
	    'separator' => ',',
	    'prefix' => '',
	    'suffix' => '',
	    'exclude' => 0,
	    'id' => 'status',
	    'table' => 'httpbl',
	    'field' => 'status',
	    'relationship' => 'none',
	  ),
	  'expire' => array(
	    'label' => 'Expires',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'date_format' => 'small',
	    'custom_date_format' => '',
	    'exclude' => 0,
	    'id' => 'expire',
	    'table' => 'httpbl',
	    'field' => 'expire',
	    'relationship' => 'none',
	  ),
	));
	$handler->override_option('sorts', array(
	  'expire' => array(
	    'order' => 'ASC',
	    'granularity' => 'second',
	    'id' => 'expire',
	    'table' => 'httpbl',
	    'field' => 'expire',
	    'relationship' => 'none',
	  ),
	));
	$handler->override_option('filters', array(
	  'status' => array(
	    'operator' => '>',
	    'value' => array(
	      'value' => '0',
	      'min' => '',
	      'max' => '',
	    ),
	    'group' => '0',
	    'exposed' => FALSE,
	    'expose' => array(
	      'operator' => FALSE,
	      'label' => '',
	    ),
	    'id' => 'status',
	    'table' => 'httpbl',
	    'field' => 'status',
	    'relationship' => 'none',
	  ),
	));
	$handler->override_option('access', array(
	  'type' => 'perm',
	  'perm' => 'access site reports',
	));
	$handler->override_option('cache', array(
	  'type' => 'none',
	));
	$handler->override_option('items_per_page', 25);
	$handler->override_option('use_pager', 'mini');
	$handler->override_option('style_options', array(
	  'grouping' => '',
	));
	$handler->override_option('row_options', array(
	  'inline' => array(
	    'hostname' => 'hostname',
	    'status' => 'status',
	    'expire' => 'expire',
	  ),
	  'separator' => '',
	));
	$handler = $view->new_display('page', 'Page', 'page_1');
	$handler->override_option('fields', array(
	  'counter' => array(
	    'label' => '#',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'exclude' => 0,
	    'id' => 'counter',
	    'table' => 'views',
	    'field' => 'counter',
	    'override' => array(
	      'button' => 'Use default',
	    ),
	    'relationship' => 'none',
	  ),
	  'hostname' => array(
	    'label' => 'Hostname',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 1,
	      'path' => 'http://www.projecthoneypot.org/search_ip.php?ip=[hostname]',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'exclude' => 0,
	    'id' => 'hostname',
	    'table' => 'httpbl',
	    'field' => 'hostname',
	    'relationship' => 'none',
	  ),
	  'status' => array(
	    'label' => 'Status',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'set_precision' => FALSE,
	    'precision' => 0,
	    'decimal' => '.',
	    'separator' => ',',
	    'prefix' => '',
	    'suffix' => '',
	    'exclude' => 0,
	    'id' => 'status',
	    'table' => 'httpbl',
	    'field' => 'status',
	    'relationship' => 'none',
	  ),
	  'expire' => array(
	    'label' => 'Expires',
	    'alter' => array(
	      'alter_text' => 0,
	      'text' => '',
	      'make_link' => 0,
	      'path' => '',
	      'link_class' => '',
	      'alt' => '',
	      'prefix' => '',
	      'suffix' => '',
	      'help' => '',
	      'trim' => 0,
	      'max_length' => '',
	      'word_boundary' => 1,
	      'ellipsis' => 1,
	      'strip_tags' => 0,
	      'html' => 0,
	    ),
	    'date_format' => 'small',
	    'custom_date_format' => '',
	    'exclude' => 0,
	    'id' => 'expire',
	    'table' => 'httpbl',
	    'field' => 'expire',
	    'relationship' => 'none',
	  ),
	));
	$handler->override_option('title', 'Honeypot Blocks');
	$handler->override_option('header', 'IP addresses blocked from access based on suspicious activity per Project Honeypot.
		
		Status of 1 = Blacklisted IPs (also inserted as banned hosts in Access table)
		Status of 2 = Greylisted IPs
		<hr / >');
	$handler->override_option('header_format', '3');
	$handler->override_option('header_empty', 1);
	$handler->override_option('empty', 'No blocked IPs at this time.');
	$handler->override_option('empty_format', '1');
	$handler->override_option('style_plugin', 'table');
	$handler->override_option('style_options', array(
	  'grouping' => '',
	  'override' => 1,
	  'sticky' => 0,
	  'order' => 'asc',
	  'columns' => array(
	    'hostname' => 'hostname',
	    'status' => 'status',
	    'expire' => 'expire',
	  ),
	  'info' => array(
	    'hostname' => array(
	      'sortable' => 1,
	      'separator' => '',
	    ),
	    'status' => array(
	      'sortable' => 1,
	      'separator' => '',
	    ),
	    'expire' => array(
	      'sortable' => 1,
	      'separator' => '',
	    ),
	  ),
	  'default' => '-1',
	));
	$handler->override_option('path', 'admin/reports/blocked_hosts');
	$handler->override_option('menu', array(
	  'type' => 'normal',
	  'title' => 'Honeypot Blocks',
	  'description' => 'Visitors blocked via Project Honeypot',
	  'weight' => '0',
	  'name' => 'admin_menu',
	));
	$handler->override_option('tab_options', array(
	  'type' => 'none',
	  'title' => '',
	  'description' => '',
	  'weight' => 0,
	));
  // End copy and paste of Export tab output.

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  // At the end, return array of default views.
  return $views;
}
