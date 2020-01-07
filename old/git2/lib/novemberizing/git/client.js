import {XMLHttpRequest} from "xmlhttprequest";

/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

export default class client {

    /**
     *
     * @param url {String} url
     * @param headers {Map} headers
     * @param body {String} body
     * @param callback {Function} resolve callback
     */
    static post(url, headers, body, callback) {
        console.log(url);
        let request = new XMLHttpRequest();
        request.open('POST', url, true);
        if(headers !== undefined) {
            headers.forEach((value, key, map) => {
                void(map);
                request.setRequestHeader(key, value);
            });
        }
        request.onreadystatechange = (event) => {
            void(event);
            if(request.readyState === 4) {
                if (request.status === 200) {
                    callback(request, undefined);
                } else {
                    callback(request, new Error(request.responseText));
                }
            }
        };
        request.send(body);
    }

    /**
     *
     * @param url {String} url
     * @param headers {Map} headers
     * @param callback {Function} resolve callback
     */
    static get(url, headers, callback) {
        let request = new XMLHttpRequest();
        request.open('GET', url, true);
        if(headers !== undefined) {
            headers.forEach((value, key, map) => {
                void(map);
                request.setRequestHeader(key, value);
            });
        }
        request.onreadystatechange = (event) => {
            void(event);
            if(request.readyState === 4) {
                if (request.status === 200) {
                    callback(request, undefined);
                } else {
                    callback(request, new Error(request.responseText));
                }
            }
        };
        request.send(null);
    }

    /**
     * generate new http header
     *
     * @param basic {Map} already defined default headers
     * @param args {pair} key & value object
     */
    static header(basic, ...args) {
        let o = new Map(basic);
        if(args) {
            args.forEach((value, index, list) => {
                void(index);
                void(list);
                if(value && value.k) {
                    o.set(value.k, value.v);
                }
            });
        }
        return o;
    }
}