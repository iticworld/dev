/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

export default class NovemberizingException extends Error {
  constructor(message){
    super();
    this.message = message;
  }
}