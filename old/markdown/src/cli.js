#!/usr/bin/env node

/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import program from 'commander';
import chalk from 'chalk';
import NovemberizingHtml from './novemberizing/html';

program
  .version('0.0.1')
  .arguments('<command> [parameters...]')
  .action((command, parameters) => {
    switch(command) {
      case 'html': NovemberizingHtml.exec(parameters); break;
      default: console.error(chalk.red(`${command} ${parameters} not support`)); break;
    }
  })
  .parse(process.argv);
