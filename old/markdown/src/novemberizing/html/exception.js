/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import NovemberizingException from '../exception';

export class NovemberizingHtmlException extends NovemberizingException {
  constructor(message){
    super();
    this.message = message;
  }
}