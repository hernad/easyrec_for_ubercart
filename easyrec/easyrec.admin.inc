<?php
// $Id: easyrec.admin.inc,v 0.95 2010/10/09 21:46:12 hass Exp $

/**
 * @file
 * Administrative page callbacks for the easyrec module.
 */

/**
 * Implementation of hook_admin_settings() for configuring the module
 */ 



function easyrec_admin_settings_form($form_state) {
  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('easyrec settings'),    
    '#description' => t('To get started  go to the <a href="@easyrec">easyrec webpage</a> and register a user so you can create a tenant and get an API key. <br /> Alternatively, you can also <a href="@easyrecSourceforge">run your own easyrec server</a>.', array('@easyrec' => 'http://easyrec.org/', '@easyrecSourceforge' => 'http://sourceforge.net/projects/easyrec/')),
  );  

  $form['account']['easyrec_apiKey'] = array(
    '#title' => t('easyrec Api Key'),
    '#type' => 'textfield',
    '#default_value' => variable_get('easyrec_apiKey', ''),
    '#size' => 45,
    '#maxlength' => 45,
    '#required' => TRUE,
    '#description' => t('Your API key allows you to access easyrec services. If you dont have an API key you can obtain one from the <a href="@easyrec">easyrec webpage</a> or your own server\'s admin tool.', array('@easyrec' => 'http://easyrec.org/')),
  );  

  $form['account']['easyrec_tenantId'] = array(
    '#title' => t('easyrec tenantId'),
    '#type' => 'textfield',
    '#default_value' => variable_get('easyrec_tenantId', ''),
    '#size' => 45,
    '#maxlength' => 45,
    '#required' => TRUE,
    '#description' => t('The easyrec tenant id identifies your shop. Note: You can have multiple shops with the same API key. If you dont have a tenant id you can obtain one from the <a href="@easyrec">easyrec webpage</a> or your own server\'s admin tool.', array('@easyrec' => 'http://easyrec.org/')),
    );  

  $form['account']['easyrec_url'] = array(
    '#title' => t('easyrec URL'),
    '#type' => 'textfield',
    '#default_value' => variable_get('easyrec_url', 'http://demo.easyrec.org:8080/'),
    '#size' => 45,
    '#maxlength' => 255,
    '#required' => TRUE,
    '#description' => t('Just change this value if you <a href="@easyrecSourceforge">installed your own easyrec server</a>.  If you are not sure what this is use "http://demo.easyrec.org:8080/".', array('@easyrecSourceforge' => 'http://sourceforge.net/projects/easyrec/')),
  );  

  $form['drawingcallback'] = array(
    '#type' => 'fieldset',
    '#title' => t('drawingcallback settings'),    
    '#description' => t('Here you can create your own <a href="@easyrecJsDoc">drawing callback</a>. A drawing callback draws recommendations retrieved from the easyrec server in JSON. <br />Note: This function will not be used unless it is EXPLICITLY selected in the recommendation block settings!', array('@easyrecJsDoc' => 'http://easyrec.org/apijs#callback')),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );  


  $easyrec_drawDrupalCustom = "function drawDrupalCustomToDiv(json,recommenderDiv){\n".
     "if(\"undefined\"==typeof(json.error) ) { // if no error show recommendations\n".
               " try{\n".
               "      var items = json.recommendeditems.item; \n".
               " }catch(e){\n".
               "     return; //no recommendations found\n".
               " }\n".
               " /* when the object is already in array format, this block will not execute */\n".
               " if( \"undefined\" == typeof(items.length) ) {\n".
               "     items = new Array(items);\n".
               " }\n".
               " // display recommendations in the DIV layer specified in the parameter recommenderDiv\n".
               " if (items.length>0) {\n".
               "     for (x=0;x<15 && x <items.length;x++) {\n".
               "           document.getElementById(recommenderDiv).innerHTML +=\n".
               "               \"<div style='width:170px;padding:5px;float:left;text-align:center;\'>\"+\n".
               "               \"<a href='\"               + items[x].url + \"'>\" +".
               "               \"<img style='width:150px;border:0px;' alt='\" + items[x].description + \"'\"+\n".
               "               \"     src='\"+ items[x].imageUrl + \"'/><br/>\"\n".
               "                + items[x].description +\n".
               "               \"</a>\" +\n".
               "               \"</div>\";\n".
               "     }\n".
               " }\n".
         "}\n".
"}\n";

  $form['drawingcallback']['easyrec_drawDrupalCustom'] = array(
    '#title' => t('drawDrupalCustom drawingcallback'),
    '#type' => 'textarea',
    '#default_value' => variable_get('easyrec_drawDrupalCustom', $easyrec_drawDrupalCustom),
    '#required' => FALSE,    
    '#rows' => 35,
    '#wysiwyg' => FALSE,
  );


  return system_settings_form($form);
}

function easyrec_admin_settings_form_validate($form, &$form_state) {
  // Trim some text values.
  $form_state['values']['easyrec_tenantId'] = trim($form_state['values']['easyrec_tenantId']);
  $form_state['values']['easyrec_apiKey'] = trim($form_state['values']['easyrec_apiKey']);
  $form_state['values']['easyrec_url'] = trim($form_state['values']['easyrec_url']);    
  $form_state['values']['easyrec_drawDrupalCustom'] = trim($form_state['values']['easyrec_drawDrupalCustom']);

}