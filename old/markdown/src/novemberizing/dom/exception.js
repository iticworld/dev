/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import NovemberizingException from '../exception';

export class NovemberizingDomException extends NovemberizingException {
  constructor(message){
    super(message);
  }
}