<?php

/**
 * @file
 * Mal search date filter pane.
 */

$plugin = array(
  'title' => t('Mal search date filter'),
  'single' => TRUE,
  'render callback' => 'search_date_filter_block_render',
  'category' => array(t('Propeople'), -9),
);

/**
 * Block render callback.
 */
function search_date_filter_block_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->content = drupal_get_form('search_date_filter_form', $conf);

  return $block;
}

/**
 * Displays a search form.
 */
function search_date_filter_form(array $form, array &$form_state, $conf) {
  ctools_form_include($form_state, 'global_search_content_type', 'mal_ctools_search_date_filter', 'plugins/content_types');
  $query = drupal_get_query_parameters();
  $get_param = variable_get('search_date_filter_get_param', 'search-start-date');

  $form['container'] = array(
    '#type' => 'container',
    '#id' => 'start-date',
    '#attributes' => array(
      'class' => array('input-group date'),
    ),
  );

  $form['container']['date'] = array(
    '#type' => 'textfield',
    '#default_value' => empty($query[$get_param]) ? NULL : $query[$get_param],
    '#size' => 'auto',
    '#attributes' => array(
      'class' => array('form-control'),
      'autocomplete' => array('off'),
      'placeholder' => t('Select course start'),
    ),
    '#theme_wrappers'   => array(),
    '#suffix' => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span>',
  );

  drupal_add_js(drupal_get_path('module', 'mal_ctools_search_date_filter') . '/js/bootstrap-datepicker.min.js');
  drupal_add_js(drupal_get_path('module', 'mal_ctools_search_date_filter') . '/js/bootstrap-datepicker.sv.min.js');
  drupal_add_js(drupal_get_path('module', 'mal_ctools_search_date_filter') . '/js/facetapi_date_popup_calendar.js');

  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array(
      'class' => array('date-popup-calendar-form-submit', 'ctools-auto-submit-click'),
      'style' => array('display:none;'),
    ),
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Form submission handler for search_api_page_search_form().
 *
 * @see user_login_form_validate()
 */
function search_date_filter_form_submit(array $form, array &$form_state) {
  $query = drupal_get_query_parameters();

  $get_param = variable_get('search_date_filter_get_param', 'search-start-date');

  $query[$get_param] = $form_state['input']['date'];

  $form_state['redirect'] = array(current_path(), array('query' => $query));

  // To completely controll the redirect destination, we need to remove the
  // 'destination' GET parameter, which would override our destination, if
  // present.
  unset($_GET['destination']);
}
