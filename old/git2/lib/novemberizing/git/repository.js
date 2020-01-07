/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import command from './command';
import pair from './pair';
import base64 from "../util/base64";

export default class repository {
    /**
     * create git repository object.
     *
     * @param url {String} http based url, not null
     * @param user {String} user account name, null or undefined
     * @param password {String} user account password, null or undefined
     */
    constructor(url, user, password){
        this.url = url;
        this.user = user ? user : undefined;
        this.password = password ? password : undefined;
        this.packs = undefined;
        this.parameters = undefined;
    }

    /**
     * retrieve authentication header
     *
     * @returns {pair} authentication header
     */
    authorization(){
        return (this.user && this.password) ? new pair('Authorization', 'Basic ' + base64.encode(this.user + ':' + this.password)) : undefined;
    }

    /**
     *
     *
     * @returns {Promise} promise
     */
    async clone() {
        try {
            this.packs = await command.upload.pack.info(this.url, this.authorization());
            console.log(this.packs);
            let res = await command.upload.pack.want(this.url, this.authorization(), this.packs);
            console.log(res);

        } catch(e) {
            // todo: how to deal with exception.
            console.log(e);
        }

    }
}
