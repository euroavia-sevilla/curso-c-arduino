/**
 * @file
 * @brief How a IoTesla node will behave
 * 
 * This module abstract widget use, using MVC paradigm:
 *  + Model: Widget data received from system scripts
 *  + View: Base HTML blocks used as view templates by this engine
 *  + Controller: This engine
 *   
 * Following this guidelines, there is no need to use customised/focalised code inside
 * this module, keeping maintenance easier.
 * 
 * This module needs a list of allowed types with their update function (or null) and an
 * allowed context list. Example:
 * 
 * var w_cfg = {
 *  'type': {
 *    'label': {},
 *    'input': {
 *      'create': function(widget) {
 *        // 
 *        // Widget specific create code here
 *        // 
 *      },
 *      'update': function(widget) {
 *        // 
 *        // Widget specific update code here
 *        // 
 *      },
 *      'click': function(e) {
 *        // 
 *        // Widget specific click code here
 *        // 
 *      }
 *    },
 *    'gauge': {}
 *  }
 * }
 * 
 * 
 * @author CieNTi <cienti@cienti.com>
 */
'use strict';

/**
 * Default widgeteer configuration
 *
 * @type       {Object}
 */
var w_cfg = {
  'log': {
    'enabled': true,
    'debug': false,
    'level': 5
  },
  'events': {
    'click': null
  },
  'context': {
    'info': true,
    'success': true,
    'warning': true,
    'danger': true,
    'default': true
  },
  'type': {
    'label': null
  },
  'zone_translation': {},
  'info': {
    'version': 'v2.5.0',
    'collection_name': '',
    'collection_version': ''
  }
};

