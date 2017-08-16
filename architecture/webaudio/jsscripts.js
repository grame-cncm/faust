/*! jQuery v1.7.1 jquery.com | jquery.org/license */
(function(a,b){function cy(a){return f.isWindow(a)?a:a.nodeType===9?a.defaultView||a.parentWindow:!1}function cv(a){if(!ck[a]){var b=c.body,d=f("<"+a+">").appendTo(b),e=d.css("display");d.remove();if(e==="none"||e===""){cl||(cl=c.createElement("iframe"),cl.frameBorder=cl.width=cl.height=0),b.appendChild(cl);if(!cm||!cl.createElement)cm=(cl.contentWindow||cl.contentDocument).document,cm.write((c.compatMode==="CSS1Compat"?"<!doctype html>":"")+"<html><body>"),cm.close();d=cm.createElement(a),cm.body.appendChild(d),e=f.css(d,"display"),b.removeChild(cl)}ck[a]=e}return ck[a]}function cu(a,b){var c={};f.each(cq.concat.apply([],cq.slice(0,b)),function(){c[this]=a});return c}function ct(){cr=b}function cs(){setTimeout(ct,0);return cr=f.now()}function cj(){try{return new a.ActiveXObject("Microsoft.XMLHTTP")}catch(b){}}function ci(){try{return new a.XMLHttpRequest}catch(b){}}function cc(a,c){a.dataFilter&&(c=a.dataFilter(c,a.dataType));var d=a.dataTypes,e={},g,h,i=d.length,j,k=d[0],l,m,n,o,p;for(g=1;g<i;g++){if(g===1)for(h in a.converters)typeof h=="string"&&(e[h.toLowerCase()]=a.converters[h]);l=k,k=d[g];if(k==="*")k=l;else if(l!=="*"&&l!==k){m=l+" "+k,n=e[m]||e["* "+k];if(!n){p=b;for(o in e){j=o.split(" ");if(j[0]===l||j[0]==="*"){p=e[j[1]+" "+k];if(p){o=e[o],o===!0?n=p:p===!0&&(n=o);break}}}}!n&&!p&&f.error("No conversion from "+m.replace(" "," to ")),n!==!0&&(c=n?n(c):p(o(c)))}}return c}function cb(a,c,d){var e=a.contents,f=a.dataTypes,g=a.responseFields,h,i,j,k;for(i in g)i in d&&(c[g[i]]=d[i]);while(f[0]==="*")f.shift(),h===b&&(h=a.mimeType||c.getResponseHeader("content-type"));if(h)for(i in e)if(e[i]&&e[i].test(h)){f.unshift(i);break}if(f[0]in d)j=f[0];else{for(i in d){if(!f[0]||a.converters[i+" "+f[0]]){j=i;break}k||(k=i)}j=j||k}if(j){j!==f[0]&&f.unshift(j);return d[j]}}function ca(a,b,c,d){if(f.isArray(b))f.each(b,function(b,e){c||bE.test(a)?d(a,e):ca(a+"["+(typeof e=="object"||f.isArray(e)?b:"")+"]",e,c,d)});else if(!c&&b!=null&&typeof b=="object")for(var e in b)ca(a+"["+e+"]",b[e],c,d);else d(a,b)}function b_(a,c){var d,e,g=f.ajaxSettings.flatOptions||{};for(d in c)c[d]!==b&&((g[d]?a:e||(e={}))[d]=c[d]);e&&f.extend(!0,a,e)}function b$(a,c,d,e,f,g){f=f||c.dataTypes[0],g=g||{},g[f]=!0;var h=a[f],i=0,j=h?h.length:0,k=a===bT,l;for(;i<j&&(k||!l);i++)l=h[i](c,d,e),typeof l=="string"&&(!k||g[l]?l=b:(c.dataTypes.unshift(l),l=b$(a,c,d,e,l,g)));(k||!l)&&!g["*"]&&(l=b$(a,c,d,e,"*",g));return l}function bZ(a){return function(b,c){typeof b!="string"&&(c=b,b="*");if(f.isFunction(c)){var d=b.toLowerCase().split(bP),e=0,g=d.length,h,i,j;for(;e<g;e++)h=d[e],j=/^\+/.test(h),j&&(h=h.substr(1)||"*"),i=a[h]=a[h]||[],i[j?"unshift":"push"](c)}}}function bC(a,b,c){var d=b==="width"?a.offsetWidth:a.offsetHeight,e=b==="width"?bx:by,g=0,h=e.length;if(d>0){if(c!=="border")for(;g<h;g++)c||(d-=parseFloat(f.css(a,"padding"+e[g]))||0),c==="margin"?d+=parseFloat(f.css(a,c+e[g]))||0:d-=parseFloat(f.css(a,"border"+e[g]+"Width"))||0;return d+"px"}d=bz(a,b,b);if(d<0||d==null)d=a.style[b]||0;d=parseFloat(d)||0;if(c)for(;g<h;g++)d+=parseFloat(f.css(a,"padding"+e[g]))||0,c!=="padding"&&(d+=parseFloat(f.css(a,"border"+e[g]+"Width"))||0),c==="margin"&&(d+=parseFloat(f.css(a,c+e[g]))||0);return d+"px"}function bp(a,b){b.src?f.ajax({url:b.src,async:!1,dataType:"script"}):f.globalEval((b.text||b.textContent||b.innerHTML||"").replace(bf,"/*$0*/")),b.parentNode&&b.parentNode.removeChild(b)}function bo(a){var b=c.createElement("div");bh.appendChild(b),b.innerHTML=a.outerHTML;return b.firstChild}function bn(a){var b=(a.nodeName||"").toLowerCase();b==="input"?bm(a):b!=="script"&&typeof a.getElementsByTagName!="undefined"&&f.grep(a.getElementsByTagName("input"),bm)}function bm(a){if(a.type==="checkbox"||a.type==="radio")a.defaultChecked=a.checked}function bl(a){return typeof a.getElementsByTagName!="undefined"?a.getElementsByTagName("*"):typeof a.querySelectorAll!="undefined"?a.querySelectorAll("*"):[]}function bk(a,b){var c;if(b.nodeType===1){b.clearAttributes&&b.clearAttributes(),b.mergeAttributes&&b.mergeAttributes(a),c=b.nodeName.toLowerCase();if(c==="object")b.outerHTML=a.outerHTML;else if(c!=="input"||a.type!=="checkbox"&&a.type!=="radio"){if(c==="option")b.selected=a.defaultSelected;else if(c==="input"||c==="textarea")b.defaultValue=a.defaultValue}else a.checked&&(b.defaultChecked=b.checked=a.checked),b.value!==a.value&&(b.value=a.value);b.removeAttribute(f.expando)}}function bj(a,b){if(b.nodeType===1&&!!f.hasData(a)){var c,d,e,g=f._data(a),h=f._data(b,g),i=g.events;if(i){delete h.handle,h.events={};for(c in i)for(d=0,e=i[c].length;d<e;d++)f.event.add(b,c+(i[c][d].namespace?".":"")+i[c][d].namespace,i[c][d],i[c][d].data)}h.data&&(h.data=f.extend({},h.data))}}function bi(a,b){return f.nodeName(a,"table")?a.getElementsByTagName("tbody")[0]||a.appendChild(a.ownerDocument.createElement("tbody")):a}function U(a){var b=V.split("|"),c=a.createDocumentFragment();if(c.createElement)while(b.length)c.createElement(b.pop());return c}function T(a,b,c){b=b||0;if(f.isFunction(b))return f.grep(a,function(a,d){var e=!!b.call(a,d,a);return e===c});if(b.nodeType)return f.grep(a,function(a,d){return a===b===c});if(typeof b=="string"){var d=f.grep(a,function(a){return a.nodeType===1});if(O.test(b))return f.filter(b,d,!c);b=f.filter(b,d)}return f.grep(a,function(a,d){return f.inArray(a,b)>=0===c})}function S(a){return!a||!a.parentNode||a.parentNode.nodeType===11}function K(){return!0}function J(){return!1}function n(a,b,c){var d=b+"defer",e=b+"queue",g=b+"mark",h=f._data(a,d);h&&(c==="queue"||!f._data(a,e))&&(c==="mark"||!f._data(a,g))&&setTimeout(function(){!f._data(a,e)&&!f._data(a,g)&&(f.removeData(a,d,!0),h.fire())},0)}function m(a){for(var b in a){if(b==="data"&&f.isEmptyObject(a[b]))continue;if(b!=="toJSON")return!1}return!0}function l(a,c,d){if(d===b&&a.nodeType===1){var e="data-"+c.replace(k,"-$1").toLowerCase();d=a.getAttribute(e);if(typeof d=="string"){try{d=d==="true"?!0:d==="false"?!1:d==="null"?null:f.isNumeric(d)?parseFloat(d):j.test(d)?f.parseJSON(d):d}catch(g){}f.data(a,c,d)}else d=b}return d}function h(a){var b=g[a]={},c,d;a=a.split(/\s+/);for(c=0,d=a.length;c<d;c++)b[a[c]]=!0;return b}var c=a.document,d=a.navigator,e=a.location,f=function(){function J(){if(!e.isReady){try{c.documentElement.doScroll("left")}catch(a){setTimeout(J,1);return}e.ready()}}var e=function(a,b){return new e.fn.init(a,b,h)},f=a.jQuery,g=a.$,h,i=/^(?:[^#<]*(<[\w\W]+>)[^>]*$|#([\w\-]*)$)/,j=/\S/,k=/^\s+/,l=/\s+$/,m=/^<(\w+)\s*\/?>(?:<\/\1>)?$/,n=/^[\],:{}\s]*$/,o=/\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g,p=/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g,q=/(?:^|:|,)(?:\s*\[)+/g,r=/(webkit)[ \/]([\w.]+)/,s=/(opera)(?:.*version)?[ \/]([\w.]+)/,t=/(msie) ([\w.]+)/,u=/(mozilla)(?:.*? rv:([\w.]+))?/,v=/-([a-z]|[0-9])/ig,w=/^-ms-/,x=function(a,b){return(b+"").toUpperCase()},y=d.userAgent,z,A,B,C=Object.prototype.toString,D=Object.prototype.hasOwnProperty,E=Array.prototype.push,F=Array.prototype.slice,G=String.prototype.trim,H=Array.prototype.indexOf,I={};e.fn=e.prototype={constructor:e,init:function(a,d,f){var g,h,j,k;if(!a)return this;if(a.nodeType){this.context=this[0]=a,this.length=1;return this}if(a==="body"&&!d&&c.body){this.context=c,this[0]=c.body,this.selector=a,this.length=1;return this}if(typeof a=="string"){a.charAt(0)!=="<"||a.charAt(a.length-1)!==">"||a.length<3?g=i.exec(a):g=[null,a,null];if(g&&(g[1]||!d)){if(g[1]){d=d instanceof e?d[0]:d,k=d?d.ownerDocument||d:c,j=m.exec(a),j?e.isPlainObject(d)?(a=[c.createElement(j[1])],e.fn.attr.call(a,d,!0)):a=[k.createElement(j[1])]:(j=e.buildFragment([g[1]],[k]),a=(j.cacheable?e.clone(j.fragment):j.fragment).childNodes);return e.merge(this,a)}h=c.getElementById(g[2]);if(h&&h.parentNode){if(h.id!==g[2])return f.find(a);this.length=1,this[0]=h}this.context=c,this.selector=a;return this}return!d||d.jquery?(d||f).find(a):this.constructor(d).find(a)}if(e.isFunction(a))return f.ready(a);a.selector!==b&&(this.selector=a.selector,this.context=a.context);return e.makeArray(a,this)},selector:"",jquery:"1.7.1",length:0,size:function(){return this.length},toArray:function(){return F.call(this,0)},get:function(a){return a==null?this.toArray():a<0?this[this.length+a]:this[a]},pushStack:function(a,b,c){var d=this.constructor();e.isArray(a)?E.apply(d,a):e.merge(d,a),d.prevObject=this,d.context=this.context,b==="find"?d.selector=this.selector+(this.selector?" ":"")+c:b&&(d.selector=this.selector+"."+b+"("+c+")");return d},each:function(a,b){return e.each(this,a,b)},ready:function(a){e.bindReady(),A.add(a);return this},eq:function(a){a=+a;return a===-1?this.slice(a):this.slice(a,a+1)},first:function(){return this.eq(0)},last:function(){return this.eq(-1)},slice:function(){return this.pushStack(F.apply(this,arguments),"slice",F.call(arguments).join(","))},map:function(a){return this.pushStack(e.map(this,function(b,c){return a.call(b,c,b)}))},end:function(){return this.prevObject||this.constructor(null)},push:E,sort:[].sort,splice:[].splice},e.fn.init.prototype=e.fn,e.extend=e.fn.extend=function(){var a,c,d,f,g,h,i=arguments[0]||{},j=1,k=arguments.length,l=!1;typeof i=="boolean"&&(l=i,i=arguments[1]||{},j=2),typeof i!="object"&&!e.isFunction(i)&&(i={}),k===j&&(i=this,--j);for(;j<k;j++)if((a=arguments[j])!=null)for(c in a){d=i[c],f=a[c];if(i===f)continue;l&&f&&(e.isPlainObject(f)||(g=e.isArray(f)))?(g?(g=!1,h=d&&e.isArray(d)?d:[]):h=d&&e.isPlainObject(d)?d:{},i[c]=e.extend(l,h,f)):f!==b&&(i[c]=f)}return i},e.extend({noConflict:function(b){a.$===e&&(a.$=g),b&&a.jQuery===e&&(a.jQuery=f);return e},isReady:!1,readyWait:1,holdReady:function(a){a?e.readyWait++:e.ready(!0)},ready:function(a){if(a===!0&&!--e.readyWait||a!==!0&&!e.isReady){if(!c.body)return setTimeout(e.ready,1);e.isReady=!0;if(a!==!0&&--e.readyWait>0)return;A.fireWith(c,[e]),e.fn.trigger&&e(c).trigger("ready").off("ready")}},bindReady:function(){if(!A){A=e.Callbacks("once memory");if(c.readyState==="complete")return setTimeout(e.ready,1);if(c.addEventListener)c.addEventListener("DOMContentLoaded",B,!1),a.addEventListener("load",e.ready,!1);else if(c.attachEvent){c.attachEvent("onreadystatechange",B),a.attachEvent("onload",e.ready);var b=!1;try{b=a.frameElement==null}catch(d){}c.documentElement.doScroll&&b&&J()}}},isFunction:function(a){return e.type(a)==="function"},isArray:Array.isArray||function(a){return e.type(a)==="array"},isWindow:function(a){return a&&typeof a=="object"&&"setInterval"in a},isNumeric:function(a){return!isNaN(parseFloat(a))&&isFinite(a)},type:function(a){return a==null?String(a):I[C.call(a)]||"object"},isPlainObject:function(a){if(!a||e.type(a)!=="object"||a.nodeType||e.isWindow(a))return!1;try{if(a.constructor&&!D.call(a,"constructor")&&!D.call(a.constructor.prototype,"isPrototypeOf"))return!1}catch(c){return!1}var d;for(d in a);return d===b||D.call(a,d)},isEmptyObject:function(a){for(var b in a)return!1;return!0},error:function(a){throw new Error(a)},parseJSON:function(b){if(typeof b!="string"||!b)return null;b=e.trim(b);if(a.JSON&&a.JSON.parse)return a.JSON.parse(b);if(n.test(b.replace(o,"@").replace(p,"]").replace(q,"")))return(new Function("return "+b))();e.error("Invalid JSON: "+b)},parseXML:function(c){var d,f;try{a.DOMParser?(f=new DOMParser,d=f.parseFromString(c,"text/xml")):(d=new ActiveXObject("Microsoft.XMLDOM"),d.async="false",d.loadXML(c))}catch(g){d=b}(!d||!d.documentElement||d.getElementsByTagName("parsererror").length)&&e.error("Invalid XML: "+c);return d},noop:function(){},globalEval:function(b){b&&j.test(b)&&(a.execScript||function(b){a.eval.call(a,b)})(b)},camelCase:function(a){return a.replace(w,"ms-").replace(v,x)},nodeName:function(a,b){return a.nodeName&&a.nodeName.toUpperCase()===b.toUpperCase()},each:function(a,c,d){var f,g=0,h=a.length,i=h===b||e.isFunction(a);if(d){if(i){for(f in a)if(c.apply(a[f],d)===!1)break}else for(;g<h;)if(c.apply(a[g++],d)===!1)break}else if(i){for(f in a)if(c.call(a[f],f,a[f])===!1)break}else for(;g<h;)if(c.call(a[g],g,a[g++])===!1)break;return a},trim:G?function(a){return a==null?"":G.call(a)}:function(a){return a==null?"":(a+"").replace(k,"").replace(l,"")},makeArray:function(a,b){var c=b||[];if(a!=null){var d=e.type(a);a.length==null||d==="string"||d==="function"||d==="regexp"||e.isWindow(a)?E.call(c,a):e.merge(c,a)}return c},inArray:function(a,b,c){var d;if(b){if(H)return H.call(b,a,c);d=b.length,c=c?c<0?Math.max(0,d+c):c:0;for(;c<d;c++)if(c in b&&b[c]===a)return c}return-1},merge:function(a,c){var d=a.length,e=0;if(typeof c.length=="number")for(var f=c.length;e<f;e++)a[d++]=c[e];else while(c[e]!==b)a[d++]=c[e++];a.length=d;return a},grep:function(a,b,c){var d=[],e;c=!!c;for(var f=0,g=a.length;f<g;f++)e=!!b(a[f],f),c!==e&&d.push(a[f]);return d},map:function(a,c,d){var f,g,h=[],i=0,j=a.length,k=a instanceof e||j!==b&&typeof j=="number"&&(j>0&&a[0]&&a[j-1]||j===0||e.isArray(a));if(k)for(;i<j;i++)f=c(a[i],i,d),f!=null&&(h[h.length]=f);else for(g in a)f=c(a[g],g,d),f!=null&&(h[h.length]=f);return h.concat.apply([],h)},guid:1,proxy:function(a,c){if(typeof c=="string"){var d=a[c];c=a,a=d}if(!e.isFunction(a))return b;var f=F.call(arguments,2),g=function(){return a.apply(c,f.concat(F.call(arguments)))};g.guid=a.guid=a.guid||g.guid||e.guid++;return g},access:function(a,c,d,f,g,h){var i=a.length;if(typeof c=="object"){for(var j in c)e.access(a,j,c[j],f,g,d);return a}if(d!==b){f=!h&&f&&e.isFunction(d);for(var k=0;k<i;k++)g(a[k],c,f?d.call(a[k],k,g(a[k],c)):d,h);return a}return i?g(a[0],c):b},now:function(){return(new Date).getTime()},uaMatch:function(a){a=a.toLowerCase();var b=r.exec(a)||s.exec(a)||t.exec(a)||a.indexOf("compatible")<0&&u.exec(a)||[];return{browser:b[1]||"",version:b[2]||"0"}},sub:function(){function a(b,c){return new a.fn.init(b,c)}e.extend(!0,a,this),a.superclass=this,a.fn=a.prototype=this(),a.fn.constructor=a,a.sub=this.sub,a.fn.init=function(d,f){f&&f instanceof e&&!(f instanceof a)&&(f=a(f));return e.fn.init.call(this,d,f,b)},a.fn.init.prototype=a.fn;var b=a(c);return a},browser:{}}),e.each("Boolean Number String Function Array Date RegExp Object".split(" "),function(a,b){I["[object "+b+"]"]=b.toLowerCase()}),z=e.uaMatch(y),z.browser&&(e.browser[z.browser]=!0,e.browser.version=z.version),e.browser.webkit&&(e.browser.safari=!0),j.test(" ")&&(k=/^[\s\xA0]+/,l=/[\s\xA0]+$/),h=e(c),c.addEventListener?B=function(){c.removeEventListener("DOMContentLoaded",B,!1),e.ready()}:c.attachEvent&&(B=function(){c.readyState==="complete"&&(c.detachEvent("onreadystatechange",B),e.ready())});return e}(),g={};f.Callbacks=function(a){a=a?g[a]||h(a):{};var c=[],d=[],e,i,j,k,l,m=function(b){var d,e,g,h,i;for(d=0,e=b.length;d<e;d++)g=b[d],h=f.type(g),h==="array"?m(g):h==="function"&&(!a.unique||!o.has(g))&&c.push(g)},n=function(b,f){f=f||[],e=!a.memory||[b,f],i=!0,l=j||0,j=0,k=c.length;for(;c&&l<k;l++)if(c[l].apply(b,f)===!1&&a.stopOnFalse){e=!0;break}i=!1,c&&(a.once?e===!0?o.disable():c=[]:d&&d.length&&(e=d.shift(),o.fireWith(e[0],e[1])))},o={add:function(){if(c){var a=c.length;m(arguments),i?k=c.length:e&&e!==!0&&(j=a,n(e[0],e[1]))}return this},remove:function(){if(c){var b=arguments,d=0,e=b.length;for(;d<e;d++)for(var f=0;f<c.length;f++)if(b[d]===c[f]){i&&f<=k&&(k--,f<=l&&l--),c.splice(f--,1);if(a.unique)break}}return this},has:function(a){if(c){var b=0,d=c.length;for(;b<d;b++)if(a===c[b])return!0}return!1},empty:function(){c=[];return this},disable:function(){c=d=e=b;return this},disabled:function(){return!c},lock:function(){d=b,(!e||e===!0)&&o.disable();return this},locked:function(){return!d},fireWith:function(b,c){d&&(i?a.once||d.push([b,c]):(!a.once||!e)&&n(b,c));return this},fire:function(){o.fireWith(this,arguments);return this},fired:function(){return!!e}};return o};var i=[].slice;f.extend({Deferred:function(a){var b=f.Callbacks("once memory"),c=f.Callbacks("once memory"),d=f.Callbacks("memory"),e="pending",g={resolve:b,reject:c,notify:d},h={done:b.add,fail:c.add,progress:d.add,state:function(){return e},isResolved:b.fired,isRejected:c.fired,then:function(a,b,c){i.done(a).fail(b).progress(c);return this},always:function(){i.done.apply(i,arguments).fail.apply(i,arguments);return this},pipe:function(a,b,c){return f.Deferred(function(d){f.each({done:[a,"resolve"],fail:[b,"reject"],progress:[c,"notify"]},function(a,b){var c=b[0],e=b[1],g;f.isFunction(c)?i[a](function(){g=c.apply(this,arguments),g&&f.isFunction(g.promise)?g.promise().then(d.resolve,d.reject,d.notify):d[e+"With"](this===i?d:this,[g])}):i[a](d[e])})}).promise()},promise:function(a){if(a==null)a=h;else for(var b in h)a[b]=h[b];return a}},i=h.promise({}),j;for(j in g)i[j]=g[j].fire,i[j+"With"]=g[j].fireWith;i.done(function(){e="resolved"},c.disable,d.lock).fail(function(){e="rejected"},b.disable,d.lock),a&&a.call(i,i);return i},when:function(a){function m(a){return function(b){e[a]=arguments.length>1?i.call(arguments,0):b,j.notifyWith(k,e)}}function l(a){return function(c){b[a]=arguments.length>1?i.call(arguments,0):c,--g||j.resolveWith(j,b)}}var b=i.call(arguments,0),c=0,d=b.length,e=Array(d),g=d,h=d,j=d<=1&&a&&f.isFunction(a.promise)?a:f.Deferred(),k=j.promise();if(d>1){for(;c<d;c++)b[c]&&b[c].promise&&f.isFunction(b[c].promise)?b[c].promise().then(l(c),j.reject,m(c)):--g;g||j.resolveWith(j,b)}else j!==a&&j.resolveWith(j,d?[a]:[]);return k}}),f.support=function(){var b,d,e,g,h,i,j,k,l,m,n,o,p,q=c.createElement("div"),r=c.documentElement;q.setAttribute("className","t"),q.innerHTML="   <link/><table></table><a href='/a' style='top:1px;float:left;opacity:.55;'>a</a><input type='checkbox'/>",d=q.getElementsByTagName("*"),e=q.getElementsByTagName("a")[0];if(!d||!d.length||!e)return{};g=c.createElement("select"),h=g.appendChild(c.createElement("option")),i=q.getElementsByTagName("input")[0],b={leadingWhitespace:q.firstChild.nodeType===3,tbody:!q.getElementsByTagName("tbody").length,htmlSerialize:!!q.getElementsByTagName("link").length,style:/top/.test(e.getAttribute("style")),hrefNormalized:e.getAttribute("href")==="/a",opacity:/^0.55/.test(e.style.opacity),cssFloat:!!e.style.cssFloat,checkOn:i.value==="on",optSelected:h.selected,getSetAttribute:q.className!=="t",enctype:!!c.createElement("form").enctype,html5Clone:c.createElement("nav").cloneNode(!0).outerHTML!=="<:nav></:nav>",submitBubbles:!0,changeBubbles:!0,focusinBubbles:!1,deleteExpando:!0,noCloneEvent:!0,inlineBlockNeedsLayout:!1,shrinkWrapBlocks:!1,reliableMarginRight:!0},i.checked=!0,b.noCloneChecked=i.cloneNode(!0).checked,g.disabled=!0,b.optDisabled=!h.disabled;try{delete q.test}catch(s){b.deleteExpando=!1}!q.addEventListener&&q.attachEvent&&q.fireEvent&&(q.attachEvent("onclick",function(){b.noCloneEvent=!1}),q.cloneNode(!0).fireEvent("onclick")),i=c.createElement("input"),i.value="t",i.setAttribute("type","radio"),b.radioValue=i.value==="t",i.setAttribute("checked","checked"),q.appendChild(i),k=c.createDocumentFragment(),k.appendChild(q.lastChild),b.checkClone=k.cloneNode(!0).cloneNode(!0).lastChild.checked,b.appendChecked=i.checked,k.removeChild(i),k.appendChild(q),q.innerHTML="",a.getComputedStyle&&(j=c.createElement("div"),j.style.width="0",j.style.marginRight="0",q.style.width="2px",q.appendChild(j),b.reliableMarginRight=(parseInt((a.getComputedStyle(j,null)||{marginRight:0}).marginRight,10)||0)===0);if(q.attachEvent)for(o in{submit:1,change:1,focusin:1})n="on"+o,p=n in q,p||(q.setAttribute(n,"return;"),p=typeof q[n]=="function"),b[o+"Bubbles"]=p;k.removeChild(q),k=g=h=j=q=i=null,f(function(){var a,d,e,g,h,i,j,k,m,n,o,r=c.getElementsByTagName("body")[0];!r||(j=1,k="position:absolute;top:0;left:0;width:1px;height:1px;margin:0;",m="visibility:hidden;border:0;",n="style='"+k+"border:5px solid #000;padding:0;'",o="<div "+n+"><div></div></div>"+"<table "+n+" cellpadding='0' cellspacing='0'>"+"<tr><td></td></tr></table>",a=c.createElement("div"),a.style.cssText=m+"width:0;height:0;position:static;top:0;margin-top:"+j+"px",r.insertBefore(a,r.firstChild),q=c.createElement("div"),a.appendChild(q),q.innerHTML="<table><tr><td style='padding:0;border:0;display:none'></td><td>t</td></tr></table>",l=q.getElementsByTagName("td"),p=l[0].offsetHeight===0,l[0].style.display="",l[1].style.display="none",b.reliableHiddenOffsets=p&&l[0].offsetHeight===0,q.innerHTML="",q.style.width=q.style.paddingLeft="1px",f.boxModel=b.boxModel=q.offsetWidth===2,typeof q.style.zoom!="undefined"&&(q.style.display="inline",q.style.zoom=1,b.inlineBlockNeedsLayout=q.offsetWidth===2,q.style.display="",q.innerHTML="<div style='width:4px;'></div>",b.shrinkWrapBlocks=q.offsetWidth!==2),q.style.cssText=k+m,q.innerHTML=o,d=q.firstChild,e=d.firstChild,h=d.nextSibling.firstChild.firstChild,i={doesNotAddBorder:e.offsetTop!==5,doesAddBorderForTableAndCells:h.offsetTop===5},e.style.position="fixed",e.style.top="20px",i.fixedPosition=e.offsetTop===20||e.offsetTop===15,e.style.position=e.style.top="",d.style.overflow="hidden",d.style.position="relative",i.subtractsBorderForOverflowNotVisible=e.offsetTop===-5,i.doesNotIncludeMarginInBodyOffset=r.offsetTop!==j,r.removeChild(a),q=a=null,f.extend(b,i))});return b}();var j=/^(?:\{.*\}|\[.*\])$/,k=/([A-Z])/g;f.extend({cache:{},uuid:0,expando:"jQuery"+(f.fn.jquery+Math.random()).replace(/\D/g,""),noData:{embed:!0,object:"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000",applet:!0},hasData:function(a){a=a.nodeType?f.cache[a[f.expando]]:a[f.expando];return!!a&&!m(a)},data:function(a,c,d,e){if(!!f.acceptData(a)){var g,h,i,j=f.expando,k=typeof c=="string",l=a.nodeType,m=l?f.cache:a,n=l?a[j]:a[j]&&j,o=c==="events";if((!n||!m[n]||!o&&!e&&!m[n].data)&&k&&d===b)return;n||(l?a[j]=n=++f.uuid:n=j),m[n]||(m[n]={},l||(m[n].toJSON=f.noop));if(typeof c=="object"||typeof c=="function")e?m[n]=f.extend(m[n],c):m[n].data=f.extend(m[n].data,c);g=h=m[n],e||(h.data||(h.data={}),h=h.data),d!==b&&(h[f.camelCase(c)]=d);if(o&&!h[c])return g.events;k?(i=h[c],i==null&&(i=h[f.camelCase(c)])):i=h;return i}},removeData:function(a,b,c){if(!!f.acceptData(a)){var d,e,g,h=f.expando,i=a.nodeType,j=i?f.cache:a,k=i?a[h]:h;if(!j[k])return;if(b){d=c?j[k]:j[k].data;if(d){f.isArray(b)||(b in d?b=[b]:(b=f.camelCase(b),b in d?b=[b]:b=b.split(" ")));for(e=0,g=b.length;e<g;e++)delete d[b[e]];if(!(c?m:f.isEmptyObject)(d))return}}if(!c){delete j[k].data;if(!m(j[k]))return}f.support.deleteExpando||!j.setInterval?delete j[k]:j[k]=null,i&&(f.support.deleteExpando?delete a[h]:a.removeAttribute?a.removeAttribute(h):a[h]=null)}},_data:function(a,b,c){return f.data(a,b,c,!0)},acceptData:function(a){if(a.nodeName){var b=f.noData[a.nodeName.toLowerCase()];if(b)return b!==!0&&a.getAttribute("classid")===b}return!0}}),f.fn.extend({data:function(a,c){var d,e,g,h=null;if(typeof a=="undefined"){if(this.length){h=f.data(this[0]);if(this[0].nodeType===1&&!f._data(this[0],"parsedAttrs")){e=this[0].attributes;for(var i=0,j=e.length;i<j;i++)g=e[i].name,g.indexOf("data-")===0&&(g=f.camelCase(g.substring(5)),l(this[0],g,h[g]));f._data(this[0],"parsedAttrs",!0)}}return h}if(typeof a=="object")return this.each(function(){f.data(this,a)});d=a.split("."),d[1]=d[1]?"."+d[1]:"";if(c===b){h=this.triggerHandler("getData"+d[1]+"!",[d[0]]),h===b&&this.length&&(h=f.data(this[0],a),h=l(this[0],a,h));return h===b&&d[1]?this.data(d[0]):h}return this.each(function(){var b=f(this),e=[d[0],c];b.triggerHandler("setData"+d[1]+"!",e),f.data(this,a,c),b.triggerHandler("changeData"+d[1]+"!",e)})},removeData:function(a){return this.each(function(){f.removeData(this,a)})}}),f.extend({_mark:function(a,b){a&&(b=(b||"fx")+"mark",f._data(a,b,(f._data(a,b)||0)+1))},_unmark:function(a,b,c){a!==!0&&(c=b,b=a,a=!1);if(b){c=c||"fx";var d=c+"mark",e=a?0:(f._data(b,d)||1)-1;e?f._data(b,d,e):(f.removeData(b,d,!0),n(b,c,"mark"))}},queue:function(a,b,c){var d;if(a){b=(b||"fx")+"queue",d=f._data(a,b),c&&(!d||f.isArray(c)?d=f._data(a,b,f.makeArray(c)):d.push(c));return d||[]}},dequeue:function(a,b){b=b||"fx";var c=f.queue(a,b),d=c.shift(),e={};d==="inprogress"&&(d=c.shift()),d&&(b==="fx"&&c.unshift("inprogress"),f._data(a,b+".run",e),d.call(a,function(){f.dequeue(a,b)},e)),c.length||(f.removeData(a,b+"queue "+b+".run",!0),n(a,b,"queue"))}}),f.fn.extend({queue:function(a,c){typeof a!="string"&&(c=a,a="fx");if(c===b)return f.queue(this[0],a);return this.each(function(){var b=f.queue(this,a,c);a==="fx"&&b[0]!=="inprogress"&&f.dequeue(this,a)})},dequeue:function(a){return this.each(function(){f.dequeue(this,a)})},delay:function(a,b){a=f.fx?f.fx.speeds[a]||a:a,b=b||"fx";return this.queue(b,function(b,c){var d=setTimeout(b,a);c.stop=function(){clearTimeout(d)}})},clearQueue:function(a){return this.queue(a||"fx",[])},promise:function(a,c){function m(){--h||d.resolveWith(e,[e])}typeof a!="string"&&(c=a,a=b),a=a||"fx";var d=f.Deferred(),e=this,g=e.length,h=1,i=a+"defer",j=a+"queue",k=a+"mark",l;while(g--)if(l=f.data(e[g],i,b,!0)||(f.data(e[g],j,b,!0)||f.data(e[g],k,b,!0))&&f.data(e[g],i,f.Callbacks("once memory"),!0))h++,l.add(m);m();return d.promise()}});var o=/[\n\t\r]/g,p=/\s+/,q=/\r/g,r=/^(?:button|input)$/i,s=/^(?:button|input|object|select|textarea)$/i,t=/^a(?:rea)?$/i,u=/^(?:autofocus|autoplay|async|checked|controls|defer|disabled|hidden|loop|multiple|open|readonly|required|scoped|selected)$/i,v=f.support.getSetAttribute,w,x,y;f.fn.extend({attr:function(a,b){return f.access(this,a,b,!0,f.attr)},removeAttr:function(a){return this.each(function(){f.removeAttr(this,a)})},prop:function(a,b){return f.access(this,a,b,!0,f.prop)},removeProp:function(a){a=f.propFix[a]||a;return this.each(function(){try{this[a]=b,delete this[a]}catch(c){}})},addClass:function(a){var b,c,d,e,g,h,i;if(f.isFunction(a))return this.each(function(b){f(this).addClass(a.call(this,b,this.className))});if(a&&typeof a=="string"){b=a.split(p);for(c=0,d=this.length;c<d;c++){e=this[c];if(e.nodeType===1)if(!e.className&&b.length===1)e.className=a;else{g=" "+e.className+" ";for(h=0,i=b.length;h<i;h++)~g.indexOf(" "+b[h]+" ")||(g+=b[h]+" ");e.className=f.trim(g)}}}return this},removeClass:function(a){var c,d,e,g,h,i,j;if(f.isFunction(a))return this.each(function(b){f(this).removeClass(a.call(this,b,this.className))});if(a&&typeof a=="string"||a===b){c=(a||"").split(p);for(d=0,e=this.length;d<e;d++){g=this[d];if(g.nodeType===1&&g.className)if(a){h=(" "+g.className+" ").replace(o," ");for(i=0,j=c.length;i<j;i++)h=h.replace(" "+c[i]+" "," ");g.className=f.trim(h)}else g.className=""}}return this},toggleClass:function(a,b){var c=typeof a,d=typeof b=="boolean";if(f.isFunction(a))return this.each(function(c){f(this).toggleClass(a.call(this,c,this.className,b),b)});return this.each(function(){if(c==="string"){var e,g=0,h=f(this),i=b,j=a.split(p);while(e=j[g++])i=d?i:!h.hasClass(e),h[i?"addClass":"removeClass"](e)}else if(c==="undefined"||c==="boolean")this.className&&f._data(this,"__className__",this.className),this.className=this.className||a===!1?"":f._data(this,"__className__")||""})},hasClass:function(a){var b=" "+a+" ",c=0,d=this.length;for(;c<d;c++)if(this[c].nodeType===1&&(" "+this[c].className+" ").replace(o," ").indexOf(b)>-1)return!0;return!1},val:function(a){var c,d,e,g=this[0];{if(!!arguments.length){e=f.isFunction(a);return this.each(function(d){var g=f(this),h;if(this.nodeType===1){e?h=a.call(this,d,g.val()):h=a,h==null?h="":typeof h=="number"?h+="":f.isArray(h)&&(h=f.map(h,function(a){return a==null?"":a+""})),c=f.valHooks[this.nodeName.toLowerCase()]||f.valHooks[this.type];if(!c||!("set"in c)||c.set(this,h,"value")===b)this.value=h}})}if(g){c=f.valHooks[g.nodeName.toLowerCase()]||f.valHooks[g.type];if(c&&"get"in c&&(d=c.get(g,"value"))!==b)return d;d=g.value;return typeof d=="string"?d.replace(q,""):d==null?"":d}}}}),f.extend({valHooks:{option:{get:function(a){var b=a.attributes.value;return!b||b.specified?a.value:a.text}},select:{get:function(a){var b,c,d,e,g=a.selectedIndex,h=[],i=a.options,j=a.type==="select-one";if(g<0)return null;c=j?g:0,d=j?g+1:i.length;for(;c<d;c++){e=i[c];if(e.selected&&(f.support.optDisabled?!e.disabled:e.getAttribute("disabled")===null)&&(!e.parentNode.disabled||!f.nodeName(e.parentNode,"optgroup"))){b=f(e).val();if(j)return b;h.push(b)}}if(j&&!h.length&&i.length)return f(i[g]).val();return h},set:function(a,b){var c=f.makeArray(b);f(a).find("option").each(function(){this.selected=f.inArray(f(this).val(),c)>=0}),c.length||(a.selectedIndex=-1);return c}}},attrFn:{val:!0,css:!0,html:!0,text:!0,data:!0,width:!0,height:!0,offset:!0},attr:function(a,c,d,e){var g,h,i,j=a.nodeType;if(!!a&&j!==3&&j!==8&&j!==2){if(e&&c in f.attrFn)return f(a)[c](d);if(typeof a.getAttribute=="undefined")return f.prop(a,c,d);i=j!==1||!f.isXMLDoc(a),i&&(c=c.toLowerCase(),h=f.attrHooks[c]||(u.test(c)?x:w));if(d!==b){if(d===null){f.removeAttr(a,c);return}if(h&&"set"in h&&i&&(g=h.set(a,d,c))!==b)return g;a.setAttribute(c,""+d);return d}if(h&&"get"in h&&i&&(g=h.get(a,c))!==null)return g;g=a.getAttribute(c);return g===null?b:g}},removeAttr:function(a,b){var c,d,e,g,h=0;if(b&&a.nodeType===1){d=b.toLowerCase().split(p),g=d.length;for(;h<g;h++)e=d[h],e&&(c=f.propFix[e]||e,f.attr(a,e,""),a.removeAttribute(v?e:c),u.test(e)&&c in a&&(a[c]=!1))}},attrHooks:{type:{set:function(a,b){if(r.test(a.nodeName)&&a.parentNode)f.error("type property can't be changed");else if(!f.support.radioValue&&b==="radio"&&f.nodeName(a,"input")){var c=a.value;a.setAttribute("type",b),c&&(a.value=c);return b}}},value:{get:function(a,b){if(w&&f.nodeName(a,"button"))return w.get(a,b);return b in a?a.value:null},set:function(a,b,c){if(w&&f.nodeName(a,"button"))return w.set(a,b,c);a.value=b}}},propFix:{tabindex:"tabIndex",readonly:"readOnly","for":"htmlFor","class":"className",maxlength:"maxLength",cellspacing:"cellSpacing",cellpadding:"cellPadding",rowspan:"rowSpan",colspan:"colSpan",usemap:"useMap",frameborder:"frameBorder",contenteditable:"contentEditable"},prop:function(a,c,d){var e,g,h,i=a.nodeType;if(!!a&&i!==3&&i!==8&&i!==2){h=i!==1||!f.isXMLDoc(a),h&&(c=f.propFix[c]||c,g=f.propHooks[c]);return d!==b?g&&"set"in g&&(e=g.set(a,d,c))!==b?e:a[c]=d:g&&"get"in g&&(e=g.get(a,c))!==null?e:a[c]}},propHooks:{tabIndex:{get:function(a){var c=a.getAttributeNode("tabindex");return c&&c.specified?parseInt(c.value,10):s.test(a.nodeName)||t.test(a.nodeName)&&a.href?0:b}}}}),f.attrHooks.tabindex=f.propHooks.tabIndex,x={get:function(a,c){var d,e=f.prop(a,c);return e===!0||typeof e!="boolean"&&(d=a.getAttributeNode(c))&&d.nodeValue!==!1?c.toLowerCase():b},set:function(a,b,c){var d;b===!1?f.removeAttr(a,c):(d=f.propFix[c]||c,d in a&&(a[d]=!0),a.setAttribute(c,c.toLowerCase()));return c}},v||(y={name:!0,id:!0},w=f.valHooks.button={get:function(a,c){var d;d=a.getAttributeNode(c);return d&&(y[c]?d.nodeValue!=="":d.specified)?d.nodeValue:b},set:function(a,b,d){var e=a.getAttributeNode(d);e||(e=c.createAttribute(d),a.setAttributeNode(e));return e.nodeValue=b+""}},f.attrHooks.tabindex.set=w.set,f.each(["width","height"],function(a,b){f.attrHooks[b]=f.extend(f.attrHooks[b],{set:function(a,c){if(c===""){a.setAttribute(b,"auto");return c}}})}),f.attrHooks.contenteditable={get:w.get,set:function(a,b,c){b===""&&(b="false"),w.set(a,b,c)}}),f.support.hrefNormalized||f.each(["href","src","width","height"],function(a,c){f.attrHooks[c]=f.extend(f.attrHooks[c],{get:function(a){var d=a.getAttribute(c,2);return d===null?b:d}})}),f.support.style||(f.attrHooks.style={get:function(a){return a.style.cssText.toLowerCase()||b},set:function(a,b){return a.style.cssText=""+b}}),f.support.optSelected||(f.propHooks.selected=f.extend(f.propHooks.selected,{get:function(a){var b=a.parentNode;b&&(b.selectedIndex,b.parentNode&&b.parentNode.selectedIndex);return null}})),f.support.enctype||(f.propFix.enctype="encoding"),f.support.checkOn||f.each(["radio","checkbox"],function(){f.valHooks[this]={get:function(a){return a.getAttribute("value")===null?"on":a.value}}}),f.each(["radio","checkbox"],function(){f.valHooks[this]=f.extend(f.valHooks[this],{set:function(a,b){if(f.isArray(b))return a.checked=f.inArray(f(a).val(),b)>=0}})});var z=/^(?:textarea|input|select)$/i,A=/^([^\.]*)?(?:\.(.+))?$/,B=/\bhover(\.\S+)?\b/,C=/^key/,D=/^(?:mouse|contextmenu)|click/,E=/^(?:focusinfocus|focusoutblur)$/,F=/^(\w*)(?:#([\w\-]+))?(?:\.([\w\-]+))?$/,G=function(a){var b=F.exec(a);b&&(b[1]=(b[1]||"").toLowerCase(),b[3]=b[3]&&new RegExp("(?:^|\\s)"+b[3]+"(?:\\s|$)"));return b},H=function(a,b){var c=a.attributes||{};return(!b[1]||a.nodeName.toLowerCase()===b[1])&&(!b[2]||(c.id||{}).value===b[2])&&(!b[3]||b[3].test((c["class"]||{}).value))},I=function(a){return f.event.special.hover?a:a.replace(B,"mouseenter$1 mouseleave$1")};
f.event={add:function(a,c,d,e,g){var h,i,j,k,l,m,n,o,p,q,r,s;if(!(a.nodeType===3||a.nodeType===8||!c||!d||!(h=f._data(a)))){d.handler&&(p=d,d=p.handler),d.guid||(d.guid=f.guid++),j=h.events,j||(h.events=j={}),i=h.handle,i||(h.handle=i=function(a){return typeof f!="undefined"&&(!a||f.event.triggered!==a.type)?f.event.dispatch.apply(i.elem,arguments):b},i.elem=a),c=f.trim(I(c)).split(" ");for(k=0;k<c.length;k++){l=A.exec(c[k])||[],m=l[1],n=(l[2]||"").split(".").sort(),s=f.event.special[m]||{},m=(g?s.delegateType:s.bindType)||m,s=f.event.special[m]||{},o=f.extend({type:m,origType:l[1],data:e,handler:d,guid:d.guid,selector:g,quick:G(g),namespace:n.join(".")},p),r=j[m];if(!r){r=j[m]=[],r.delegateCount=0;if(!s.setup||s.setup.call(a,e,n,i)===!1)a.addEventListener?a.addEventListener(m,i,!1):a.attachEvent&&a.attachEvent("on"+m,i)}s.add&&(s.add.call(a,o),o.handler.guid||(o.handler.guid=d.guid)),g?r.splice(r.delegateCount++,0,o):r.push(o),f.event.global[m]=!0}a=null}},global:{},remove:function(a,b,c,d,e){var g=f.hasData(a)&&f._data(a),h,i,j,k,l,m,n,o,p,q,r,s;if(!!g&&!!(o=g.events)){b=f.trim(I(b||"")).split(" ");for(h=0;h<b.length;h++){i=A.exec(b[h])||[],j=k=i[1],l=i[2];if(!j){for(j in o)f.event.remove(a,j+b[h],c,d,!0);continue}p=f.event.special[j]||{},j=(d?p.delegateType:p.bindType)||j,r=o[j]||[],m=r.length,l=l?new RegExp("(^|\\.)"+l.split(".").sort().join("\\.(?:.*\\.)?")+"(\\.|$)"):null;for(n=0;n<r.length;n++)s=r[n],(e||k===s.origType)&&(!c||c.guid===s.guid)&&(!l||l.test(s.namespace))&&(!d||d===s.selector||d==="**"&&s.selector)&&(r.splice(n--,1),s.selector&&r.delegateCount--,p.remove&&p.remove.call(a,s));r.length===0&&m!==r.length&&((!p.teardown||p.teardown.call(a,l)===!1)&&f.removeEvent(a,j,g.handle),delete o[j])}f.isEmptyObject(o)&&(q=g.handle,q&&(q.elem=null),f.removeData(a,["events","handle"],!0))}},customEvent:{getData:!0,setData:!0,changeData:!0},trigger:function(c,d,e,g){if(!e||e.nodeType!==3&&e.nodeType!==8){var h=c.type||c,i=[],j,k,l,m,n,o,p,q,r,s;if(E.test(h+f.event.triggered))return;h.indexOf("!")>=0&&(h=h.slice(0,-1),k=!0),h.indexOf(".")>=0&&(i=h.split("."),h=i.shift(),i.sort());if((!e||f.event.customEvent[h])&&!f.event.global[h])return;c=typeof c=="object"?c[f.expando]?c:new f.Event(h,c):new f.Event(h),c.type=h,c.isTrigger=!0,c.exclusive=k,c.namespace=i.join("."),c.namespace_re=c.namespace?new RegExp("(^|\\.)"+i.join("\\.(?:.*\\.)?")+"(\\.|$)"):null,o=h.indexOf(":")<0?"on"+h:"";if(!e){j=f.cache;for(l in j)j[l].events&&j[l].events[h]&&f.event.trigger(c,d,j[l].handle.elem,!0);return}c.result=b,c.target||(c.target=e),d=d!=null?f.makeArray(d):[],d.unshift(c),p=f.event.special[h]||{};if(p.trigger&&p.trigger.apply(e,d)===!1)return;r=[[e,p.bindType||h]];if(!g&&!p.noBubble&&!f.isWindow(e)){s=p.delegateType||h,m=E.test(s+h)?e:e.parentNode,n=null;for(;m;m=m.parentNode)r.push([m,s]),n=m;n&&n===e.ownerDocument&&r.push([n.defaultView||n.parentWindow||a,s])}for(l=0;l<r.length&&!c.isPropagationStopped();l++)m=r[l][0],c.type=r[l][1],q=(f._data(m,"events")||{})[c.type]&&f._data(m,"handle"),q&&q.apply(m,d),q=o&&m[o],q&&f.acceptData(m)&&q.apply(m,d)===!1&&c.preventDefault();c.type=h,!g&&!c.isDefaultPrevented()&&(!p._default||p._default.apply(e.ownerDocument,d)===!1)&&(h!=="click"||!f.nodeName(e,"a"))&&f.acceptData(e)&&o&&e[h]&&(h!=="focus"&&h!=="blur"||c.target.offsetWidth!==0)&&!f.isWindow(e)&&(n=e[o],n&&(e[o]=null),f.event.triggered=h,e[h](),f.event.triggered=b,n&&(e[o]=n));return c.result}},dispatch:function(c){c=f.event.fix(c||a.event);var d=(f._data(this,"events")||{})[c.type]||[],e=d.delegateCount,g=[].slice.call(arguments,0),h=!c.exclusive&&!c.namespace,i=[],j,k,l,m,n,o,p,q,r,s,t;g[0]=c,c.delegateTarget=this;if(e&&!c.target.disabled&&(!c.button||c.type!=="click")){m=f(this),m.context=this.ownerDocument||this;for(l=c.target;l!=this;l=l.parentNode||this){o={},q=[],m[0]=l;for(j=0;j<e;j++)r=d[j],s=r.selector,o[s]===b&&(o[s]=r.quick?H(l,r.quick):m.is(s)),o[s]&&q.push(r);q.length&&i.push({elem:l,matches:q})}}d.length>e&&i.push({elem:this,matches:d.slice(e)});for(j=0;j<i.length&&!c.isPropagationStopped();j++){p=i[j],c.currentTarget=p.elem;for(k=0;k<p.matches.length&&!c.isImmediatePropagationStopped();k++){r=p.matches[k];if(h||!c.namespace&&!r.namespace||c.namespace_re&&c.namespace_re.test(r.namespace))c.data=r.data,c.handleObj=r,n=((f.event.special[r.origType]||{}).handle||r.handler).apply(p.elem,g),n!==b&&(c.result=n,n===!1&&(c.preventDefault(),c.stopPropagation()))}}return c.result},props:"attrChange attrName relatedNode srcElement altKey bubbles cancelable ctrlKey currentTarget eventPhase metaKey relatedTarget shiftKey target timeStamp view which".split(" "),fixHooks:{},keyHooks:{props:"char charCode key keyCode".split(" "),filter:function(a,b){a.which==null&&(a.which=b.charCode!=null?b.charCode:b.keyCode);return a}},mouseHooks:{props:"button buttons clientX clientY fromElement offsetX offsetY pageX pageY screenX screenY toElement".split(" "),filter:function(a,d){var e,f,g,h=d.button,i=d.fromElement;a.pageX==null&&d.clientX!=null&&(e=a.target.ownerDocument||c,f=e.documentElement,g=e.body,a.pageX=d.clientX+(f&&f.scrollLeft||g&&g.scrollLeft||0)-(f&&f.clientLeft||g&&g.clientLeft||0),a.pageY=d.clientY+(f&&f.scrollTop||g&&g.scrollTop||0)-(f&&f.clientTop||g&&g.clientTop||0)),!a.relatedTarget&&i&&(a.relatedTarget=i===a.target?d.toElement:i),!a.which&&h!==b&&(a.which=h&1?1:h&2?3:h&4?2:0);return a}},fix:function(a){if(a[f.expando])return a;var d,e,g=a,h=f.event.fixHooks[a.type]||{},i=h.props?this.props.concat(h.props):this.props;a=f.Event(g);for(d=i.length;d;)e=i[--d],a[e]=g[e];a.target||(a.target=g.srcElement||c),a.target.nodeType===3&&(a.target=a.target.parentNode),a.metaKey===b&&(a.metaKey=a.ctrlKey);return h.filter?h.filter(a,g):a},special:{ready:{setup:f.bindReady},load:{noBubble:!0},focus:{delegateType:"focusin"},blur:{delegateType:"focusout"},beforeunload:{setup:function(a,b,c){f.isWindow(this)&&(this.onbeforeunload=c)},teardown:function(a,b){this.onbeforeunload===b&&(this.onbeforeunload=null)}}},simulate:function(a,b,c,d){var e=f.extend(new f.Event,c,{type:a,isSimulated:!0,originalEvent:{}});d?f.event.trigger(e,null,b):f.event.dispatch.call(b,e),e.isDefaultPrevented()&&c.preventDefault()}},f.event.handle=f.event.dispatch,f.removeEvent=c.removeEventListener?function(a,b,c){a.removeEventListener&&a.removeEventListener(b,c,!1)}:function(a,b,c){a.detachEvent&&a.detachEvent("on"+b,c)},f.Event=function(a,b){if(!(this instanceof f.Event))return new f.Event(a,b);a&&a.type?(this.originalEvent=a,this.type=a.type,this.isDefaultPrevented=a.defaultPrevented||a.returnValue===!1||a.getPreventDefault&&a.getPreventDefault()?K:J):this.type=a,b&&f.extend(this,b),this.timeStamp=a&&a.timeStamp||f.now(),this[f.expando]=!0},f.Event.prototype={preventDefault:function(){this.isDefaultPrevented=K;var a=this.originalEvent;!a||(a.preventDefault?a.preventDefault():a.returnValue=!1)},stopPropagation:function(){this.isPropagationStopped=K;var a=this.originalEvent;!a||(a.stopPropagation&&a.stopPropagation(),a.cancelBubble=!0)},stopImmediatePropagation:function(){this.isImmediatePropagationStopped=K,this.stopPropagation()},isDefaultPrevented:J,isPropagationStopped:J,isImmediatePropagationStopped:J},f.each({mouseenter:"mouseover",mouseleave:"mouseout"},function(a,b){f.event.special[a]={delegateType:b,bindType:b,handle:function(a){var c=this,d=a.relatedTarget,e=a.handleObj,g=e.selector,h;if(!d||d!==c&&!f.contains(c,d))a.type=e.origType,h=e.handler.apply(this,arguments),a.type=b;return h}}}),f.support.submitBubbles||(f.event.special.submit={setup:function(){if(f.nodeName(this,"form"))return!1;f.event.add(this,"click._submit keypress._submit",function(a){var c=a.target,d=f.nodeName(c,"input")||f.nodeName(c,"button")?c.form:b;d&&!d._submit_attached&&(f.event.add(d,"submit._submit",function(a){this.parentNode&&!a.isTrigger&&f.event.simulate("submit",this.parentNode,a,!0)}),d._submit_attached=!0)})},teardown:function(){if(f.nodeName(this,"form"))return!1;f.event.remove(this,"._submit")}}),f.support.changeBubbles||(f.event.special.change={setup:function(){if(z.test(this.nodeName)){if(this.type==="checkbox"||this.type==="radio")f.event.add(this,"propertychange._change",function(a){a.originalEvent.propertyName==="checked"&&(this._just_changed=!0)}),f.event.add(this,"click._change",function(a){this._just_changed&&!a.isTrigger&&(this._just_changed=!1,f.event.simulate("change",this,a,!0))});return!1}f.event.add(this,"beforeactivate._change",function(a){var b=a.target;z.test(b.nodeName)&&!b._change_attached&&(f.event.add(b,"change._change",function(a){this.parentNode&&!a.isSimulated&&!a.isTrigger&&f.event.simulate("change",this.parentNode,a,!0)}),b._change_attached=!0)})},handle:function(a){var b=a.target;if(this!==b||a.isSimulated||a.isTrigger||b.type!=="radio"&&b.type!=="checkbox")return a.handleObj.handler.apply(this,arguments)},teardown:function(){f.event.remove(this,"._change");return z.test(this.nodeName)}}),f.support.focusinBubbles||f.each({focus:"focusin",blur:"focusout"},function(a,b){var d=0,e=function(a){f.event.simulate(b,a.target,f.event.fix(a),!0)};f.event.special[b]={setup:function(){d++===0&&c.addEventListener(a,e,!0)},teardown:function(){--d===0&&c.removeEventListener(a,e,!0)}}}),f.fn.extend({on:function(a,c,d,e,g){var h,i;if(typeof a=="object"){typeof c!="string"&&(d=c,c=b);for(i in a)this.on(i,c,d,a[i],g);return this}d==null&&e==null?(e=c,d=c=b):e==null&&(typeof c=="string"?(e=d,d=b):(e=d,d=c,c=b));if(e===!1)e=J;else if(!e)return this;g===1&&(h=e,e=function(a){f().off(a);return h.apply(this,arguments)},e.guid=h.guid||(h.guid=f.guid++));return this.each(function(){f.event.add(this,a,e,d,c)})},one:function(a,b,c,d){return this.on.call(this,a,b,c,d,1)},off:function(a,c,d){if(a&&a.preventDefault&&a.handleObj){var e=a.handleObj;f(a.delegateTarget).off(e.namespace?e.type+"."+e.namespace:e.type,e.selector,e.handler);return this}if(typeof a=="object"){for(var g in a)this.off(g,c,a[g]);return this}if(c===!1||typeof c=="function")d=c,c=b;d===!1&&(d=J);return this.each(function(){f.event.remove(this,a,d,c)})},bind:function(a,b,c){return this.on(a,null,b,c)},unbind:function(a,b){return this.off(a,null,b)},live:function(a,b,c){f(this.context).on(a,this.selector,b,c);return this},die:function(a,b){f(this.context).off(a,this.selector||"**",b);return this},delegate:function(a,b,c,d){return this.on(b,a,c,d)},undelegate:function(a,b,c){return arguments.length==1?this.off(a,"**"):this.off(b,a,c)},trigger:function(a,b){return this.each(function(){f.event.trigger(a,b,this)})},triggerHandler:function(a,b){if(this[0])return f.event.trigger(a,b,this[0],!0)},toggle:function(a){var b=arguments,c=a.guid||f.guid++,d=0,e=function(c){var e=(f._data(this,"lastToggle"+a.guid)||0)%d;f._data(this,"lastToggle"+a.guid,e+1),c.preventDefault();return b[e].apply(this,arguments)||!1};e.guid=c;while(d<b.length)b[d++].guid=c;return this.click(e)},hover:function(a,b){return this.mouseenter(a).mouseleave(b||a)}}),f.each("blur focus focusin focusout load resize scroll unload click dblclick mousedown mouseup mousemove mouseover mouseout mouseenter mouseleave change select submit keydown keypress keyup error contextmenu".split(" "),function(a,b){f.fn[b]=function(a,c){c==null&&(c=a,a=null);return arguments.length>0?this.on(b,null,a,c):this.trigger(b)},f.attrFn&&(f.attrFn[b]=!0),C.test(b)&&(f.event.fixHooks[b]=f.event.keyHooks),D.test(b)&&(f.event.fixHooks[b]=f.event.mouseHooks)}),function(){function x(a,b,c,e,f,g){for(var h=0,i=e.length;h<i;h++){var j=e[h];if(j){var k=!1;j=j[a];while(j){if(j[d]===c){k=e[j.sizset];break}if(j.nodeType===1){g||(j[d]=c,j.sizset=h);if(typeof b!="string"){if(j===b){k=!0;break}}else if(m.filter(b,[j]).length>0){k=j;break}}j=j[a]}e[h]=k}}}function w(a,b,c,e,f,g){for(var h=0,i=e.length;h<i;h++){var j=e[h];if(j){var k=!1;j=j[a];while(j){if(j[d]===c){k=e[j.sizset];break}j.nodeType===1&&!g&&(j[d]=c,j.sizset=h);if(j.nodeName.toLowerCase()===b){k=j;break}j=j[a]}e[h]=k}}}var a=/((?:\((?:\([^()]+\)|[^()]+)+\)|\[(?:\[[^\[\]]*\]|['"][^'"]*['"]|[^\[\]'"]+)+\]|\\.|[^ >+~,(\[\\]+)+|[>+~])(\s*,\s*)?((?:.|\r|\n)*)/g,d="sizcache"+(Math.random()+"").replace(".",""),e=0,g=Object.prototype.toString,h=!1,i=!0,j=/\\/g,k=/\r\n/g,l=/\W/;[0,0].sort(function(){i=!1;return 0});var m=function(b,d,e,f){e=e||[],d=d||c;var h=d;if(d.nodeType!==1&&d.nodeType!==9)return[];if(!b||typeof b!="string")return e;var i,j,k,l,n,q,r,t,u=!0,v=m.isXML(d),w=[],x=b;do{a.exec(""),i=a.exec(x);if(i){x=i[3],w.push(i[1]);if(i[2]){l=i[3];break}}}while(i);if(w.length>1&&p.exec(b))if(w.length===2&&o.relative[w[0]])j=y(w[0]+w[1],d,f);else{j=o.relative[w[0]]?[d]:m(w.shift(),d);while(w.length)b=w.shift(),o.relative[b]&&(b+=w.shift()),j=y(b,j,f)}else{!f&&w.length>1&&d.nodeType===9&&!v&&o.match.ID.test(w[0])&&!o.match.ID.test(w[w.length-1])&&(n=m.find(w.shift(),d,v),d=n.expr?m.filter(n.expr,n.set)[0]:n.set[0]);if(d){n=f?{expr:w.pop(),set:s(f)}:m.find(w.pop(),w.length===1&&(w[0]==="~"||w[0]==="+")&&d.parentNode?d.parentNode:d,v),j=n.expr?m.filter(n.expr,n.set):n.set,w.length>0?k=s(j):u=!1;while(w.length)q=w.pop(),r=q,o.relative[q]?r=w.pop():q="",r==null&&(r=d),o.relative[q](k,r,v)}else k=w=[]}k||(k=j),k||m.error(q||b);if(g.call(k)==="[object Array]")if(!u)e.push.apply(e,k);else if(d&&d.nodeType===1)for(t=0;k[t]!=null;t++)k[t]&&(k[t]===!0||k[t].nodeType===1&&m.contains(d,k[t]))&&e.push(j[t]);else for(t=0;k[t]!=null;t++)k[t]&&k[t].nodeType===1&&e.push(j[t]);else s(k,e);l&&(m(l,h,e,f),m.uniqueSort(e));return e};m.uniqueSort=function(a){if(u){h=i,a.sort(u);if(h)for(var b=1;b<a.length;b++)a[b]===a[b-1]&&a.splice(b--,1)}return a},m.matches=function(a,b){return m(a,null,null,b)},m.matchesSelector=function(a,b){return m(b,null,null,[a]).length>0},m.find=function(a,b,c){var d,e,f,g,h,i;if(!a)return[];for(e=0,f=o.order.length;e<f;e++){h=o.order[e];if(g=o.leftMatch[h].exec(a)){i=g[1],g.splice(1,1);if(i.substr(i.length-1)!=="\\"){g[1]=(g[1]||"").replace(j,""),d=o.find[h](g,b,c);if(d!=null){a=a.replace(o.match[h],"");break}}}}d||(d=typeof b.getElementsByTagName!="undefined"?b.getElementsByTagName("*"):[]);return{set:d,expr:a}},m.filter=function(a,c,d,e){var f,g,h,i,j,k,l,n,p,q=a,r=[],s=c,t=c&&c[0]&&m.isXML(c[0]);while(a&&c.length){for(h in o.filter)if((f=o.leftMatch[h].exec(a))!=null&&f[2]){k=o.filter[h],l=f[1],g=!1,f.splice(1,1);if(l.substr(l.length-1)==="\\")continue;s===r&&(r=[]);if(o.preFilter[h]){f=o.preFilter[h](f,s,d,r,e,t);if(!f)g=i=!0;else if(f===!0)continue}if(f)for(n=0;(j=s[n])!=null;n++)j&&(i=k(j,f,n,s),p=e^i,d&&i!=null?p?g=!0:s[n]=!1:p&&(r.push(j),g=!0));if(i!==b){d||(s=r),a=a.replace(o.match[h],"");if(!g)return[];break}}if(a===q)if(g==null)m.error(a);else break;q=a}return s},m.error=function(a){throw new Error("Syntax error, unrecognized expression: "+a)};var n=m.getText=function(a){var b,c,d=a.nodeType,e="";if(d){if(d===1||d===9){if(typeof a.textContent=="string")return a.textContent;if(typeof a.innerText=="string")return a.innerText.replace(k,"");for(a=a.firstChild;a;a=a.nextSibling)e+=n(a)}else if(d===3||d===4)return a.nodeValue}else for(b=0;c=a[b];b++)c.nodeType!==8&&(e+=n(c));return e},o=m.selectors={order:["ID","NAME","TAG"],match:{ID:/#((?:[\w\u00c0-\uFFFF\-]|\\.)+)/,CLASS:/\.((?:[\w\u00c0-\uFFFF\-]|\\.)+)/,NAME:/\[name=['"]*((?:[\w\u00c0-\uFFFF\-]|\\.)+)['"]*\]/,ATTR:/\[\s*((?:[\w\u00c0-\uFFFF\-]|\\.)+)\s*(?:(\S?=)\s*(?:(['"])(.*?)\3|(#?(?:[\w\u00c0-\uFFFF\-]|\\.)*)|)|)\s*\]/,TAG:/^((?:[\w\u00c0-\uFFFF\*\-]|\\.)+)/,CHILD:/:(only|nth|last|first)-child(?:\(\s*(even|odd|(?:[+\-]?\d+|(?:[+\-]?\d*)?n\s*(?:[+\-]\s*\d+)?))\s*\))?/,POS:/:(nth|eq|gt|lt|first|last|even|odd)(?:\((\d*)\))?(?=[^\-]|$)/,PSEUDO:/:((?:[\w\u00c0-\uFFFF\-]|\\.)+)(?:\((['"]?)((?:\([^\)]+\)|[^\(\)]*)+)\2\))?/},leftMatch:{},attrMap:{"class":"className","for":"htmlFor"},attrHandle:{href:function(a){return a.getAttribute("href")},type:function(a){return a.getAttribute("type")}},relative:{"+":function(a,b){var c=typeof b=="string",d=c&&!l.test(b),e=c&&!d;d&&(b=b.toLowerCase());for(var f=0,g=a.length,h;f<g;f++)if(h=a[f]){while((h=h.previousSibling)&&h.nodeType!==1);a[f]=e||h&&h.nodeName.toLowerCase()===b?h||!1:h===b}e&&m.filter(b,a,!0)},">":function(a,b){var c,d=typeof b=="string",e=0,f=a.length;if(d&&!l.test(b)){b=b.toLowerCase();for(;e<f;e++){c=a[e];if(c){var g=c.parentNode;a[e]=g.nodeName.toLowerCase()===b?g:!1}}}else{for(;e<f;e++)c=a[e],c&&(a[e]=d?c.parentNode:c.parentNode===b);d&&m.filter(b,a,!0)}},"":function(a,b,c){var d,f=e++,g=x;typeof b=="string"&&!l.test(b)&&(b=b.toLowerCase(),d=b,g=w),g("parentNode",b,f,a,d,c)},"~":function(a,b,c){var d,f=e++,g=x;typeof b=="string"&&!l.test(b)&&(b=b.toLowerCase(),d=b,g=w),g("previousSibling",b,f,a,d,c)}},find:{ID:function(a,b,c){if(typeof b.getElementById!="undefined"&&!c){var d=b.getElementById(a[1]);return d&&d.parentNode?[d]:[]}},NAME:function(a,b){if(typeof b.getElementsByName!="undefined"){var c=[],d=b.getElementsByName(a[1]);for(var e=0,f=d.length;e<f;e++)d[e].getAttribute("name")===a[1]&&c.push(d[e]);return c.length===0?null:c}},TAG:function(a,b){if(typeof b.getElementsByTagName!="undefined")return b.getElementsByTagName(a[1])}},preFilter:{CLASS:function(a,b,c,d,e,f){a=" "+a[1].replace(j,"")+" ";if(f)return a;for(var g=0,h;(h=b[g])!=null;g++)h&&(e^(h.className&&(" "+h.className+" ").replace(/[\t\n\r]/g," ").indexOf(a)>=0)?c||d.push(h):c&&(b[g]=!1));return!1},ID:function(a){return a[1].replace(j,"")},TAG:function(a,b){return a[1].replace(j,"").toLowerCase()},CHILD:function(a){if(a[1]==="nth"){a[2]||m.error(a[0]),a[2]=a[2].replace(/^\+|\s*/g,"");var b=/(-?)(\d*)(?:n([+\-]?\d*))?/.exec(a[2]==="even"&&"2n"||a[2]==="odd"&&"2n+1"||!/\D/.test(a[2])&&"0n+"+a[2]||a[2]);a[2]=b[1]+(b[2]||1)-0,a[3]=b[3]-0}else a[2]&&m.error(a[0]);a[0]=e++;return a},ATTR:function(a,b,c,d,e,f){var g=a[1]=a[1].replace(j,"");!f&&o.attrMap[g]&&(a[1]=o.attrMap[g]),a[4]=(a[4]||a[5]||"").replace(j,""),a[2]==="~="&&(a[4]=" "+a[4]+" ");return a},PSEUDO:function(b,c,d,e,f){if(b[1]==="not")if((a.exec(b[3])||"").length>1||/^\w/.test(b[3]))b[3]=m(b[3],null,null,c);else{var g=m.filter(b[3],c,d,!0^f);d||e.push.apply(e,g);return!1}else if(o.match.POS.test(b[0])||o.match.CHILD.test(b[0]))return!0;return b},POS:function(a){a.unshift(!0);return a}},filters:{enabled:function(a){return a.disabled===!1&&a.type!=="hidden"},disabled:function(a){return a.disabled===!0},checked:function(a){return a.checked===!0},selected:function(a){a.parentNode&&a.parentNode.selectedIndex;return a.selected===!0},parent:function(a){return!!a.firstChild},empty:function(a){return!a.firstChild},has:function(a,b,c){return!!m(c[3],a).length},header:function(a){return/h\d/i.test(a.nodeName)},text:function(a){var b=a.getAttribute("type"),c=a.type;return a.nodeName.toLowerCase()==="input"&&"text"===c&&(b===c||b===null)},radio:function(a){return a.nodeName.toLowerCase()==="input"&&"radio"===a.type},checkbox:function(a){return a.nodeName.toLowerCase()==="input"&&"checkbox"===a.type},file:function(a){return a.nodeName.toLowerCase()==="input"&&"file"===a.type},password:function(a){return a.nodeName.toLowerCase()==="input"&&"password"===a.type},submit:function(a){var b=a.nodeName.toLowerCase();return(b==="input"||b==="button")&&"submit"===a.type},image:function(a){return a.nodeName.toLowerCase()==="input"&&"image"===a.type},reset:function(a){var b=a.nodeName.toLowerCase();return(b==="input"||b==="button")&&"reset"===a.type},button:function(a){var b=a.nodeName.toLowerCase();return b==="input"&&"button"===a.type||b==="button"},input:function(a){return/input|select|textarea|button/i.test(a.nodeName)},focus:function(a){return a===a.ownerDocument.activeElement}},setFilters:{first:function(a,b){return b===0},last:function(a,b,c,d){return b===d.length-1},even:function(a,b){return b%2===0},odd:function(a,b){return b%2===1},lt:function(a,b,c){return b<c[3]-0},gt:function(a,b,c){return b>c[3]-0},nth:function(a,b,c){return c[3]-0===b},eq:function(a,b,c){return c[3]-0===b}},filter:{PSEUDO:function(a,b,c,d){var e=b[1],f=o.filters[e];if(f)return f(a,c,b,d);if(e==="contains")return(a.textContent||a.innerText||n([a])||"").indexOf(b[3])>=0;if(e==="not"){var g=b[3];for(var h=0,i=g.length;h<i;h++)if(g[h]===a)return!1;return!0}m.error(e)},CHILD:function(a,b){var c,e,f,g,h,i,j,k=b[1],l=a;switch(k){case"only":case"first":while(l=l.previousSibling)if(l.nodeType===1)return!1;if(k==="first")return!0;l=a;case"last":while(l=l.nextSibling)if(l.nodeType===1)return!1;return!0;case"nth":c=b[2],e=b[3];if(c===1&&e===0)return!0;f=b[0],g=a.parentNode;if(g&&(g[d]!==f||!a.nodeIndex)){i=0;for(l=g.firstChild;l;l=l.nextSibling)l.nodeType===1&&(l.nodeIndex=++i);g[d]=f}j=a.nodeIndex-e;return c===0?j===0:j%c===0&&j/c>=0}},ID:function(a,b){return a.nodeType===1&&a.getAttribute("id")===b},TAG:function(a,b){return b==="*"&&a.nodeType===1||!!a.nodeName&&a.nodeName.toLowerCase()===b},CLASS:function(a,b){return(" "+(a.className||a.getAttribute("class"))+" ").indexOf(b)>-1},ATTR:function(a,b){var c=b[1],d=m.attr?m.attr(a,c):o.attrHandle[c]?o.attrHandle[c](a):a[c]!=null?a[c]:a.getAttribute(c),e=d+"",f=b[2],g=b[4];return d==null?f==="!=":!f&&m.attr?d!=null:f==="="?e===g:f==="*="?e.indexOf(g)>=0:f==="~="?(" "+e+" ").indexOf(g)>=0:g?f==="!="?e!==g:f==="^="?e.indexOf(g)===0:f==="$="?e.substr(e.length-g.length)===g:f==="|="?e===g||e.substr(0,g.length+1)===g+"-":!1:e&&d!==!1},POS:function(a,b,c,d){var e=b[2],f=o.setFilters[e];if(f)return f(a,c,b,d)}}},p=o.match.POS,q=function(a,b){return"\\"+(b-0+1)};for(var r in o.match)o.match[r]=new RegExp(o.match[r].source+/(?![^\[]*\])(?![^\(]*\))/.source),o.leftMatch[r]=new RegExp(/(^(?:.|\r|\n)*?)/.source+o.match[r].source.replace(/\\(\d+)/g,q));var s=function(a,b){a=Array.prototype.slice.call(a,0);if(b){b.push.apply(b,a);return b}return a};try{Array.prototype.slice.call(c.documentElement.childNodes,0)[0].nodeType}catch(t){s=function(a,b){var c=0,d=b||[];if(g.call(a)==="[object Array]")Array.prototype.push.apply(d,a);else if(typeof a.length=="number")for(var e=a.length;c<e;c++)d.push(a[c]);else for(;a[c];c++)d.push(a[c]);return d}}var u,v;c.documentElement.compareDocumentPosition?u=function(a,b){if(a===b){h=!0;return 0}if(!a.compareDocumentPosition||!b.compareDocumentPosition)return a.compareDocumentPosition?-1:1;return a.compareDocumentPosition(b)&4?-1:1}:(u=function(a,b){if(a===b){h=!0;return 0}if(a.sourceIndex&&b.sourceIndex)return a.sourceIndex-b.sourceIndex;var c,d,e=[],f=[],g=a.parentNode,i=b.parentNode,j=g;if(g===i)return v(a,b);if(!g)return-1;if(!i)return 1;while(j)e.unshift(j),j=j.parentNode;j=i;while(j)f.unshift(j),j=j.parentNode;c=e.length,d=f.length;for(var k=0;k<c&&k<d;k++)if(e[k]!==f[k])return v(e[k],f[k]);return k===c?v(a,f[k],-1):v(e[k],b,1)},v=function(a,b,c){if(a===b)return c;var d=a.nextSibling;while(d){if(d===b)return-1;d=d.nextSibling}return 1}),function(){var a=c.createElement("div"),d="script"+(new Date).getTime(),e=c.documentElement;a.innerHTML="<a name='"+d+"'/>",e.insertBefore(a,e.firstChild),c.getElementById(d)&&(o.find.ID=function(a,c,d){if(typeof c.getElementById!="undefined"&&!d){var e=c.getElementById(a[1]);return e?e.id===a[1]||typeof e.getAttributeNode!="undefined"&&e.getAttributeNode("id").nodeValue===a[1]?[e]:b:[]}},o.filter.ID=function(a,b){var c=typeof a.getAttributeNode!="undefined"&&a.getAttributeNode("id");return a.nodeType===1&&c&&c.nodeValue===b}),e.removeChild(a),e=a=null}(),function(){var a=c.createElement("div");a.appendChild(c.createComment("")),a.getElementsByTagName("*").length>0&&(o.find.TAG=function(a,b){var c=b.getElementsByTagName(a[1]);if(a[1]==="*"){var d=[];for(var e=0;c[e];e++)c[e].nodeType===1&&d.push(c[e]);c=d}return c}),a.innerHTML="<a href='#'></a>",a.firstChild&&typeof a.firstChild.getAttribute!="undefined"&&a.firstChild.getAttribute("href")!=="#"&&(o.attrHandle.href=function(a){return a.getAttribute("href",2)}),a=null}(),c.querySelectorAll&&function(){var a=m,b=c.createElement("div"),d="__sizzle__";b.innerHTML="<p class='TEST'></p>";if(!b.querySelectorAll||b.querySelectorAll(".TEST").length!==0){m=function(b,e,f,g){e=e||c;if(!g&&!m.isXML(e)){var h=/^(\w+$)|^\.([\w\-]+$)|^#([\w\-]+$)/.exec(b);if(h&&(e.nodeType===1||e.nodeType===9)){if(h[1])return s(e.getElementsByTagName(b),f);if(h[2]&&o.find.CLASS&&e.getElementsByClassName)return s(e.getElementsByClassName(h[2]),f)}if(e.nodeType===9){if(b==="body"&&e.body)return s([e.body],f);if(h&&h[3]){var i=e.getElementById(h[3]);if(!i||!i.parentNode)return s([],f);if(i.id===h[3])return s([i],f)}try{return s(e.querySelectorAll(b),f)}catch(j){}}else if(e.nodeType===1&&e.nodeName.toLowerCase()!=="object"){var k=e,l=e.getAttribute("id"),n=l||d,p=e.parentNode,q=/^\s*[+~]/.test(b);l?n=n.replace(/'/g,"\\$&"):e.setAttribute("id",n),q&&p&&(e=e.parentNode);try{if(!q||p)return s(e.querySelectorAll("[id='"+n+"'] "+b),f)}catch(r){}finally{l||k.removeAttribute("id")}}}return a(b,e,f,g)};for(var e in a)m[e]=a[e];b=null}}(),function(){var a=c.documentElement,b=a.matchesSelector||a.mozMatchesSelector||a.webkitMatchesSelector||a.msMatchesSelector;if(b){var d=!b.call(c.createElement("div"),"div"),e=!1;try{b.call(c.documentElement,"[test!='']:sizzle")}catch(f){e=!0}m.matchesSelector=function(a,c){c=c.replace(/\=\s*([^'"\]]*)\s*\]/g,"='$1']");if(!m.isXML(a))try{if(e||!o.match.PSEUDO.test(c)&&!/!=/.test(c)){var f=b.call(a,c);if(f||!d||a.document&&a.document.nodeType!==11)return f}}catch(g){}return m(c,null,null,[a]).length>0}}}(),function(){var a=c.createElement("div");a.innerHTML="<div class='test e'></div><div class='test'></div>";if(!!a.getElementsByClassName&&a.getElementsByClassName("e").length!==0){a.lastChild.className="e";if(a.getElementsByClassName("e").length===1)return;o.order.splice(1,0,"CLASS"),o.find.CLASS=function(a,b,c){if(typeof b.getElementsByClassName!="undefined"&&!c)return b.getElementsByClassName(a[1])},a=null}}(),c.documentElement.contains?m.contains=function(a,b){return a!==b&&(a.contains?a.contains(b):!0)}:c.documentElement.compareDocumentPosition?m.contains=function(a,b){return!!(a.compareDocumentPosition(b)&16)}:m.contains=function(){return!1},m.isXML=function(a){var b=(a?a.ownerDocument||a:0).documentElement;return b?b.nodeName!=="HTML":!1};var y=function(a,b,c){var d,e=[],f="",g=b.nodeType?[b]:b;while(d=o.match.PSEUDO.exec(a))f+=d[0],a=a.replace(o.match.PSEUDO,"");a=o.relative[a]?a+"*":a;for(var h=0,i=g.length;h<i;h++)m(a,g[h],e,c);return m.filter(f,e)};m.attr=f.attr,m.selectors.attrMap={},f.find=m,f.expr=m.selectors,f.expr[":"]=f.expr.filters,f.unique=m.uniqueSort,f.text=m.getText,f.isXMLDoc=m.isXML,f.contains=m.contains}();var L=/Until$/,M=/^(?:parents|prevUntil|prevAll)/,N=/,/,O=/^.[^:#\[\.,]*$/,P=Array.prototype.slice,Q=f.expr.match.POS,R={children:!0,contents:!0,next:!0,prev:!0};f.fn.extend({find:function(a){var b=this,c,d;if(typeof a!="string")return f(a).filter(function(){for(c=0,d=b.length;c<d;c++)if(f.contains(b[c],this))return!0});var e=this.pushStack("","find",a),g,h,i;for(c=0,d=this.length;c<d;c++){g=e.length,f.find(a,this[c],e);if(c>0)for(h=g;h<e.length;h++)for(i=0;i<g;i++)if(e[i]===e[h]){e.splice(h--,1);break}}return e},has:function(a){var b=f(a);return this.filter(function(){for(var a=0,c=b.length;a<c;a++)if(f.contains(this,b[a]))return!0})},not:function(a){return this.pushStack(T(this,a,!1),"not",a)},filter:function(a){return this.pushStack(T(this,a,!0),"filter",a)},is:function(a){return!!a&&(typeof a=="string"?Q.test(a)?f(a,this.context).index(this[0])>=0:f.filter(a,this).length>0:this.filter(a).length>0)},closest:function(a,b){var c=[],d,e,g=this[0];if(f.isArray(a)){var h=1;while(g&&g.ownerDocument&&g!==b){for(d=0;d<a.length;d++)f(g).is(a[d])&&c.push({selector:a[d],elem:g,level:h});g=g.parentNode,h++}return c}var i=Q.test(a)||typeof a!="string"?f(a,b||this.context):0;for(d=0,e=this.length;d<e;d++){g=this[d];while(g){if(i?i.index(g)>-1:f.find.matchesSelector(g,a)){c.push(g);break}g=g.parentNode;if(!g||!g.ownerDocument||g===b||g.nodeType===11)break}}c=c.length>1?f.unique(c):c;return this.pushStack(c,"closest",a)},index:function(a){if(!a)return this[0]&&this[0].parentNode?this.prevAll().length:-1;if(typeof a=="string")return f.inArray(this[0],f(a));return f.inArray(a.jquery?a[0]:a,this)},add:function(a,b){var c=typeof a=="string"?f(a,b):f.makeArray(a&&a.nodeType?[a]:a),d=f.merge(this.get(),c);return this.pushStack(S(c[0])||S(d[0])?d:f.unique(d))},andSelf:function(){return this.add(this.prevObject)}}),f.each({parent:function(a){var b=a.parentNode;return b&&b.nodeType!==11?b:null},parents:function(a){return f.dir(a,"parentNode")},parentsUntil:function(a,b,c){return f.dir(a,"parentNode",c)},next:function(a){return f.nth(a,2,"nextSibling")},prev:function(a){return f.nth(a,2,"previousSibling")},nextAll:function(a){return f.dir(a,"nextSibling")},prevAll:function(a){return f.dir(a,"previousSibling")},nextUntil:function(a,b,c){return f.dir(a,"nextSibling",c)},prevUntil:function(a,b,c){return f.dir(a,"previousSibling",c)},siblings:function(a){return f.sibling(a.parentNode.firstChild,a)},children:function(a){return f.sibling(a.firstChild)},contents:function(a){return f.nodeName(a,"iframe")?a.contentDocument||a.contentWindow.document:f.makeArray(a.childNodes)}},function(a,b){f.fn[a]=function(c,d){var e=f.map(this,b,c);L.test(a)||(d=c),d&&typeof d=="string"&&(e=f.filter(d,e)),e=this.length>1&&!R[a]?f.unique(e):e,(this.length>1||N.test(d))&&M.test(a)&&(e=e.reverse());return this.pushStack(e,a,P.call(arguments).join(","))}}),f.extend({filter:function(a,b,c){c&&(a=":not("+a+")");return b.length===1?f.find.matchesSelector(b[0],a)?[b[0]]:[]:f.find.matches(a,b)},dir:function(a,c,d){var e=[],g=a[c];while(g&&g.nodeType!==9&&(d===b||g.nodeType!==1||!f(g).is(d)))g.nodeType===1&&e.push(g),g=g[c];return e},nth:function(a,b,c,d){b=b||1;var e=0;for(;a;a=a[c])if(a.nodeType===1&&++e===b)break;return a},sibling:function(a,b){var c=[];for(;a;a=a.nextSibling)a.nodeType===1&&a!==b&&c.push(a);return c}});var V="abbr|article|aside|audio|canvas|datalist|details|figcaption|figure|footer|header|hgroup|mark|meter|nav|output|progress|section|summary|time|video",W=/ jQuery\d+="(?:\d+|null)"/g,X=/^\s+/,Y=/<(?!area|br|col|embed|hr|img|input|link|meta|param)(([\w:]+)[^>]*)\/>/ig,Z=/<([\w:]+)/,$=/<tbody/i,_=/<|&#?\w+;/,ba=/<(?:script|style)/i,bb=/<(?:script|object|embed|option|style)/i,bc=new RegExp("<(?:"+V+")","i"),bd=/checked\s*(?:[^=]|=\s*.checked.)/i,be=/\/(java|ecma)script/i,bf=/^\s*<!(?:\[CDATA\[|\-\-)/,bg={option:[1,"<select multiple='multiple'>","</select>"],legend:[1,"<fieldset>","</fieldset>"],thead:[1,"<table>","</table>"],tr:[2,"<table><tbody>","</tbody></table>"],td:[3,"<table><tbody><tr>","</tr></tbody></table>"],col:[2,"<table><tbody></tbody><colgroup>","</colgroup></table>"],area:[1,"<map>","</map>"],_default:[0,"",""]},bh=U(c);bg.optgroup=bg.option,bg.tbody=bg.tfoot=bg.colgroup=bg.caption=bg.thead,bg.th=bg.td,f.support.htmlSerialize||(bg._default=[1,"div<div>","</div>"]),f.fn.extend({text:function(a){if(f.isFunction(a))return this.each(function(b){var c=f(this);c.text(a.call(this,b,c.text()))});if(typeof a!="object"&&a!==b)return this.empty().append((this[0]&&this[0].ownerDocument||c).createTextNode(a));return f.text(this)},wrapAll:function(a){if(f.isFunction(a))return this.each(function(b){f(this).wrapAll(a.call(this,b))});if(this[0]){var b=f(a,this[0].ownerDocument).eq(0).clone(!0);this[0].parentNode&&b.insertBefore(this[0]),b.map(function(){var a=this;while(a.firstChild&&a.firstChild.nodeType===1)a=a.firstChild;return a}).append(this)}return this},wrapInner:function(a){if(f.isFunction(a))return this.each(function(b){f(this).wrapInner(a.call(this,b))});return this.each(function(){var b=f(this),c=b.contents();c.length?c.wrapAll(a):b.append(a)})},wrap:function(a){var b=f.isFunction(a);return this.each(function(c){f(this).wrapAll(b?a.call(this,c):a)})},unwrap:function(){return this.parent().each(function(){f.nodeName(this,"body")||f(this).replaceWith(this.childNodes)}).end()},append:function(){return this.domManip(arguments,!0,function(a){this.nodeType===1&&this.appendChild(a)})},prepend:function(){return this.domManip(arguments,!0,function(a){this.nodeType===1&&this.insertBefore(a,this.firstChild)})},before:function(){if(this[0]&&this[0].parentNode)return this.domManip(arguments,!1,function(a){this.parentNode.insertBefore(a,this)});if(arguments.length){var a=f.clean(arguments);a.push.apply(a,this.toArray());return this.pushStack(a,"before",arguments)}},after:function(){if(this[0]&&this[0].parentNode)return this.domManip(arguments,!1,function(a){this.parentNode.insertBefore(a,this.nextSibling)});if(arguments.length){var a=this.pushStack(this,"after",arguments);a.push.apply(a,f.clean(arguments));return a}},remove:function(a,b){for(var c=0,d;(d=this[c])!=null;c++)if(!a||f.filter(a,[d]).length)!b&&d.nodeType===1&&(f.cleanData(d.getElementsByTagName("*")),f.cleanData([d])),d.parentNode&&d.parentNode.removeChild(d);return this},empty:function()
{for(var a=0,b;(b=this[a])!=null;a++){b.nodeType===1&&f.cleanData(b.getElementsByTagName("*"));while(b.firstChild)b.removeChild(b.firstChild)}return this},clone:function(a,b){a=a==null?!1:a,b=b==null?a:b;return this.map(function(){return f.clone(this,a,b)})},html:function(a){if(a===b)return this[0]&&this[0].nodeType===1?this[0].innerHTML.replace(W,""):null;if(typeof a=="string"&&!ba.test(a)&&(f.support.leadingWhitespace||!X.test(a))&&!bg[(Z.exec(a)||["",""])[1].toLowerCase()]){a=a.replace(Y,"<$1></$2>");try{for(var c=0,d=this.length;c<d;c++)this[c].nodeType===1&&(f.cleanData(this[c].getElementsByTagName("*")),this[c].innerHTML=a)}catch(e){this.empty().append(a)}}else f.isFunction(a)?this.each(function(b){var c=f(this);c.html(a.call(this,b,c.html()))}):this.empty().append(a);return this},replaceWith:function(a){if(this[0]&&this[0].parentNode){if(f.isFunction(a))return this.each(function(b){var c=f(this),d=c.html();c.replaceWith(a.call(this,b,d))});typeof a!="string"&&(a=f(a).detach());return this.each(function(){var b=this.nextSibling,c=this.parentNode;f(this).remove(),b?f(b).before(a):f(c).append(a)})}return this.length?this.pushStack(f(f.isFunction(a)?a():a),"replaceWith",a):this},detach:function(a){return this.remove(a,!0)},domManip:function(a,c,d){var e,g,h,i,j=a[0],k=[];if(!f.support.checkClone&&arguments.length===3&&typeof j=="string"&&bd.test(j))return this.each(function(){f(this).domManip(a,c,d,!0)});if(f.isFunction(j))return this.each(function(e){var g=f(this);a[0]=j.call(this,e,c?g.html():b),g.domManip(a,c,d)});if(this[0]){i=j&&j.parentNode,f.support.parentNode&&i&&i.nodeType===11&&i.childNodes.length===this.length?e={fragment:i}:e=f.buildFragment(a,this,k),h=e.fragment,h.childNodes.length===1?g=h=h.firstChild:g=h.firstChild;if(g){c=c&&f.nodeName(g,"tr");for(var l=0,m=this.length,n=m-1;l<m;l++)d.call(c?bi(this[l],g):this[l],e.cacheable||m>1&&l<n?f.clone(h,!0,!0):h)}k.length&&f.each(k,bp)}return this}}),f.buildFragment=function(a,b,d){var e,g,h,i,j=a[0];b&&b[0]&&(i=b[0].ownerDocument||b[0]),i.createDocumentFragment||(i=c),a.length===1&&typeof j=="string"&&j.length<512&&i===c&&j.charAt(0)==="<"&&!bb.test(j)&&(f.support.checkClone||!bd.test(j))&&(f.support.html5Clone||!bc.test(j))&&(g=!0,h=f.fragments[j],h&&h!==1&&(e=h)),e||(e=i.createDocumentFragment(),f.clean(a,i,e,d)),g&&(f.fragments[j]=h?e:1);return{fragment:e,cacheable:g}},f.fragments={},f.each({appendTo:"append",prependTo:"prepend",insertBefore:"before",insertAfter:"after",replaceAll:"replaceWith"},function(a,b){f.fn[a]=function(c){var d=[],e=f(c),g=this.length===1&&this[0].parentNode;if(g&&g.nodeType===11&&g.childNodes.length===1&&e.length===1){e[b](this[0]);return this}for(var h=0,i=e.length;h<i;h++){var j=(h>0?this.clone(!0):this).get();f(e[h])[b](j),d=d.concat(j)}return this.pushStack(d,a,e.selector)}}),f.extend({clone:function(a,b,c){var d,e,g,h=f.support.html5Clone||!bc.test("<"+a.nodeName)?a.cloneNode(!0):bo(a);if((!f.support.noCloneEvent||!f.support.noCloneChecked)&&(a.nodeType===1||a.nodeType===11)&&!f.isXMLDoc(a)){bk(a,h),d=bl(a),e=bl(h);for(g=0;d[g];++g)e[g]&&bk(d[g],e[g])}if(b){bj(a,h);if(c){d=bl(a),e=bl(h);for(g=0;d[g];++g)bj(d[g],e[g])}}d=e=null;return h},clean:function(a,b,d,e){var g;b=b||c,typeof b.createElement=="undefined"&&(b=b.ownerDocument||b[0]&&b[0].ownerDocument||c);var h=[],i;for(var j=0,k;(k=a[j])!=null;j++){typeof k=="number"&&(k+="");if(!k)continue;if(typeof k=="string")if(!_.test(k))k=b.createTextNode(k);else{k=k.replace(Y,"<$1></$2>");var l=(Z.exec(k)||["",""])[1].toLowerCase(),m=bg[l]||bg._default,n=m[0],o=b.createElement("div");b===c?bh.appendChild(o):U(b).appendChild(o),o.innerHTML=m[1]+k+m[2];while(n--)o=o.lastChild;if(!f.support.tbody){var p=$.test(k),q=l==="table"&&!p?o.firstChild&&o.firstChild.childNodes:m[1]==="<table>"&&!p?o.childNodes:[];for(i=q.length-1;i>=0;--i)f.nodeName(q[i],"tbody")&&!q[i].childNodes.length&&q[i].parentNode.removeChild(q[i])}!f.support.leadingWhitespace&&X.test(k)&&o.insertBefore(b.createTextNode(X.exec(k)[0]),o.firstChild),k=o.childNodes}var r;if(!f.support.appendChecked)if(k[0]&&typeof (r=k.length)=="number")for(i=0;i<r;i++)bn(k[i]);else bn(k);k.nodeType?h.push(k):h=f.merge(h,k)}if(d){g=function(a){return!a.type||be.test(a.type)};for(j=0;h[j];j++)if(e&&f.nodeName(h[j],"script")&&(!h[j].type||h[j].type.toLowerCase()==="text/javascript"))e.push(h[j].parentNode?h[j].parentNode.removeChild(h[j]):h[j]);else{if(h[j].nodeType===1){var s=f.grep(h[j].getElementsByTagName("script"),g);h.splice.apply(h,[j+1,0].concat(s))}d.appendChild(h[j])}}return h},cleanData:function(a){var b,c,d=f.cache,e=f.event.special,g=f.support.deleteExpando;for(var h=0,i;(i=a[h])!=null;h++){if(i.nodeName&&f.noData[i.nodeName.toLowerCase()])continue;c=i[f.expando];if(c){b=d[c];if(b&&b.events){for(var j in b.events)e[j]?f.event.remove(i,j):f.removeEvent(i,j,b.handle);b.handle&&(b.handle.elem=null)}g?delete i[f.expando]:i.removeAttribute&&i.removeAttribute(f.expando),delete d[c]}}}});var bq=/alpha\([^)]*\)/i,br=/opacity=([^)]*)/,bs=/([A-Z]|^ms)/g,bt=/^-?\d+(?:px)?$/i,bu=/^-?\d/,bv=/^([\-+])=([\-+.\de]+)/,bw={position:"absolute",visibility:"hidden",display:"block"},bx=["Left","Right"],by=["Top","Bottom"],bz,bA,bB;f.fn.css=function(a,c){if(arguments.length===2&&c===b)return this;return f.access(this,a,c,!0,function(a,c,d){return d!==b?f.style(a,c,d):f.css(a,c)})},f.extend({cssHooks:{opacity:{get:function(a,b){if(b){var c=bz(a,"opacity","opacity");return c===""?"1":c}return a.style.opacity}}},cssNumber:{fillOpacity:!0,fontWeight:!0,lineHeight:!0,opacity:!0,orphans:!0,widows:!0,zIndex:!0,zoom:!0},cssProps:{"float":f.support.cssFloat?"cssFloat":"styleFloat"},style:function(a,c,d,e){if(!!a&&a.nodeType!==3&&a.nodeType!==8&&!!a.style){var g,h,i=f.camelCase(c),j=a.style,k=f.cssHooks[i];c=f.cssProps[i]||i;if(d===b){if(k&&"get"in k&&(g=k.get(a,!1,e))!==b)return g;return j[c]}h=typeof d,h==="string"&&(g=bv.exec(d))&&(d=+(g[1]+1)*+g[2]+parseFloat(f.css(a,c)),h="number");if(d==null||h==="number"&&isNaN(d))return;h==="number"&&!f.cssNumber[i]&&(d+="px");if(!k||!("set"in k)||(d=k.set(a,d))!==b)try{j[c]=d}catch(l){}}},css:function(a,c,d){var e,g;c=f.camelCase(c),g=f.cssHooks[c],c=f.cssProps[c]||c,c==="cssFloat"&&(c="float");if(g&&"get"in g&&(e=g.get(a,!0,d))!==b)return e;if(bz)return bz(a,c)},swap:function(a,b,c){var d={};for(var e in b)d[e]=a.style[e],a.style[e]=b[e];c.call(a);for(e in b)a.style[e]=d[e]}}),f.curCSS=f.css,f.each(["height","width"],function(a,b){f.cssHooks[b]={get:function(a,c,d){var e;if(c){if(a.offsetWidth!==0)return bC(a,b,d);f.swap(a,bw,function(){e=bC(a,b,d)});return e}},set:function(a,b){if(!bt.test(b))return b;b=parseFloat(b);if(b>=0)return b+"px"}}}),f.support.opacity||(f.cssHooks.opacity={get:function(a,b){return br.test((b&&a.currentStyle?a.currentStyle.filter:a.style.filter)||"")?parseFloat(RegExp.$1)/100+"":b?"1":""},set:function(a,b){var c=a.style,d=a.currentStyle,e=f.isNumeric(b)?"alpha(opacity="+b*100+")":"",g=d&&d.filter||c.filter||"";c.zoom=1;if(b>=1&&f.trim(g.replace(bq,""))===""){c.removeAttribute("filter");if(d&&!d.filter)return}c.filter=bq.test(g)?g.replace(bq,e):g+" "+e}}),f(function(){f.support.reliableMarginRight||(f.cssHooks.marginRight={get:function(a,b){var c;f.swap(a,{display:"inline-block"},function(){b?c=bz(a,"margin-right","marginRight"):c=a.style.marginRight});return c}})}),c.defaultView&&c.defaultView.getComputedStyle&&(bA=function(a,b){var c,d,e;b=b.replace(bs,"-$1").toLowerCase(),(d=a.ownerDocument.defaultView)&&(e=d.getComputedStyle(a,null))&&(c=e.getPropertyValue(b),c===""&&!f.contains(a.ownerDocument.documentElement,a)&&(c=f.style(a,b)));return c}),c.documentElement.currentStyle&&(bB=function(a,b){var c,d,e,f=a.currentStyle&&a.currentStyle[b],g=a.style;f===null&&g&&(e=g[b])&&(f=e),!bt.test(f)&&bu.test(f)&&(c=g.left,d=a.runtimeStyle&&a.runtimeStyle.left,d&&(a.runtimeStyle.left=a.currentStyle.left),g.left=b==="fontSize"?"1em":f||0,f=g.pixelLeft+"px",g.left=c,d&&(a.runtimeStyle.left=d));return f===""?"auto":f}),bz=bA||bB,f.expr&&f.expr.filters&&(f.expr.filters.hidden=function(a){var b=a.offsetWidth,c=a.offsetHeight;return b===0&&c===0||!f.support.reliableHiddenOffsets&&(a.style&&a.style.display||f.css(a,"display"))==="none"},f.expr.filters.visible=function(a){return!f.expr.filters.hidden(a)});var bD=/%20/g,bE=/\[\]$/,bF=/\r?\n/g,bG=/#.*$/,bH=/^(.*?):[ \t]*([^\r\n]*)\r?$/mg,bI=/^(?:color|date|datetime|datetime-local|email|hidden|month|number|password|range|search|tel|text|time|url|week)$/i,bJ=/^(?:about|app|app\-storage|.+\-extension|file|res|widget):$/,bK=/^(?:GET|HEAD)$/,bL=/^\/\//,bM=/\?/,bN=/<script\b[^<]*(?:(?!<\/script>)<[^<]*)*<\/script>/gi,bO=/^(?:select|textarea)/i,bP=/\s+/,bQ=/([?&])_=[^&]*/,bR=/^([\w\+\.\-]+:)(?:\/\/([^\/?#:]*)(?::(\d+))?)?/,bS=f.fn.load,bT={},bU={},bV,bW,bX=["*/"]+["*"];try{bV=e.href}catch(bY){bV=c.createElement("a"),bV.href="",bV=bV.href}bW=bR.exec(bV.toLowerCase())||[],f.fn.extend({load:function(a,c,d){if(typeof a!="string"&&bS)return bS.apply(this,arguments);if(!this.length)return this;var e=a.indexOf(" ");if(e>=0){var g=a.slice(e,a.length);a=a.slice(0,e)}var h="GET";c&&(f.isFunction(c)?(d=c,c=b):typeof c=="object"&&(c=f.param(c,f.ajaxSettings.traditional),h="POST"));var i=this;f.ajax({url:a,type:h,dataType:"html",data:c,complete:function(a,b,c){c=a.responseText,a.isResolved()&&(a.done(function(a){c=a}),i.html(g?f("<div>").append(c.replace(bN,"")).find(g):c)),d&&i.each(d,[c,b,a])}});return this},serialize:function(){return f.param(this.serializeArray())},serializeArray:function(){return this.map(function(){return this.elements?f.makeArray(this.elements):this}).filter(function(){return this.name&&!this.disabled&&(this.checked||bO.test(this.nodeName)||bI.test(this.type))}).map(function(a,b){var c=f(this).val();return c==null?null:f.isArray(c)?f.map(c,function(a,c){return{name:b.name,value:a.replace(bF,"\r\n")}}):{name:b.name,value:c.replace(bF,"\r\n")}}).get()}}),f.each("ajaxStart ajaxStop ajaxComplete ajaxError ajaxSuccess ajaxSend".split(" "),function(a,b){f.fn[b]=function(a){return this.on(b,a)}}),f.each(["get","post"],function(a,c){f[c]=function(a,d,e,g){f.isFunction(d)&&(g=g||e,e=d,d=b);return f.ajax({type:c,url:a,data:d,success:e,dataType:g})}}),f.extend({getScript:function(a,c){return f.get(a,b,c,"script")},getJSON:function(a,b,c){return f.get(a,b,c,"json")},ajaxSetup:function(a,b){b?b_(a,f.ajaxSettings):(b=a,a=f.ajaxSettings),b_(a,b);return a},ajaxSettings:{url:bV,isLocal:bJ.test(bW[1]),global:!0,type:"GET",contentType:"application/x-www-form-urlencoded",processData:!0,async:!0,accepts:{xml:"application/xml, text/xml",html:"text/html",text:"text/plain",json:"application/json, text/javascript","*":bX},contents:{xml:/xml/,html:/html/,json:/json/},responseFields:{xml:"responseXML",text:"responseText"},converters:{"* text":a.String,"text html":!0,"text json":f.parseJSON,"text xml":f.parseXML},flatOptions:{context:!0,url:!0}},ajaxPrefilter:bZ(bT),ajaxTransport:bZ(bU),ajax:function(a,c){function w(a,c,l,m){if(s!==2){s=2,q&&clearTimeout(q),p=b,n=m||"",v.readyState=a>0?4:0;var o,r,u,w=c,x=l?cb(d,v,l):b,y,z;if(a>=200&&a<300||a===304){if(d.ifModified){if(y=v.getResponseHeader("Last-Modified"))f.lastModified[k]=y;if(z=v.getResponseHeader("Etag"))f.etag[k]=z}if(a===304)w="notmodified",o=!0;else try{r=cc(d,x),w="success",o=!0}catch(A){w="parsererror",u=A}}else{u=w;if(!w||a)w="error",a<0&&(a=0)}v.status=a,v.statusText=""+(c||w),o?h.resolveWith(e,[r,w,v]):h.rejectWith(e,[v,w,u]),v.statusCode(j),j=b,t&&g.trigger("ajax"+(o?"Success":"Error"),[v,d,o?r:u]),i.fireWith(e,[v,w]),t&&(g.trigger("ajaxComplete",[v,d]),--f.active||f.event.trigger("ajaxStop"))}}typeof a=="object"&&(c=a,a=b),c=c||{};var d=f.ajaxSetup({},c),e=d.context||d,g=e!==d&&(e.nodeType||e instanceof f)?f(e):f.event,h=f.Deferred(),i=f.Callbacks("once memory"),j=d.statusCode||{},k,l={},m={},n,o,p,q,r,s=0,t,u,v={readyState:0,setRequestHeader:function(a,b){if(!s){var c=a.toLowerCase();a=m[c]=m[c]||a,l[a]=b}return this},getAllResponseHeaders:function(){return s===2?n:null},getResponseHeader:function(a){var c;if(s===2){if(!o){o={};while(c=bH.exec(n))o[c[1].toLowerCase()]=c[2]}c=o[a.toLowerCase()]}return c===b?null:c},overrideMimeType:function(a){s||(d.mimeType=a);return this},abort:function(a){a=a||"abort",p&&p.abort(a),w(0,a);return this}};h.promise(v),v.success=v.done,v.error=v.fail,v.complete=i.add,v.statusCode=function(a){if(a){var b;if(s<2)for(b in a)j[b]=[j[b],a[b]];else b=a[v.status],v.then(b,b)}return this},d.url=((a||d.url)+"").replace(bG,"").replace(bL,bW[1]+"//"),d.dataTypes=f.trim(d.dataType||"*").toLowerCase().split(bP),d.crossDomain==null&&(r=bR.exec(d.url.toLowerCase()),d.crossDomain=!(!r||r[1]==bW[1]&&r[2]==bW[2]&&(r[3]||(r[1]==="http:"?80:443))==(bW[3]||(bW[1]==="http:"?80:443)))),d.data&&d.processData&&typeof d.data!="string"&&(d.data=f.param(d.data,d.traditional)),b$(bT,d,c,v);if(s===2)return!1;t=d.global,d.type=d.type.toUpperCase(),d.hasContent=!bK.test(d.type),t&&f.active++===0&&f.event.trigger("ajaxStart");if(!d.hasContent){d.data&&(d.url+=(bM.test(d.url)?"&":"?")+d.data,delete d.data),k=d.url;if(d.cache===!1){var x=f.now(),y=d.url.replace(bQ,"$1_="+x);d.url=y+(y===d.url?(bM.test(d.url)?"&":"?")+"_="+x:"")}}(d.data&&d.hasContent&&d.contentType!==!1||c.contentType)&&v.setRequestHeader("Content-Type",d.contentType),d.ifModified&&(k=k||d.url,f.lastModified[k]&&v.setRequestHeader("If-Modified-Since",f.lastModified[k]),f.etag[k]&&v.setRequestHeader("If-None-Match",f.etag[k])),v.setRequestHeader("Accept",d.dataTypes[0]&&d.accepts[d.dataTypes[0]]?d.accepts[d.dataTypes[0]]+(d.dataTypes[0]!=="*"?", "+bX+"; q=0.01":""):d.accepts["*"]);for(u in d.headers)v.setRequestHeader(u,d.headers[u]);if(d.beforeSend&&(d.beforeSend.call(e,v,d)===!1||s===2)){v.abort();return!1}for(u in{success:1,error:1,complete:1})v[u](d[u]);p=b$(bU,d,c,v);if(!p)w(-1,"No Transport");else{v.readyState=1,t&&g.trigger("ajaxSend",[v,d]),d.async&&d.timeout>0&&(q=setTimeout(function(){v.abort("timeout")},d.timeout));try{s=1,p.send(l,w)}catch(z){if(s<2)w(-1,z);else throw z}}return v},param:function(a,c){var d=[],e=function(a,b){b=f.isFunction(b)?b():b,d[d.length]=encodeURIComponent(a)+"="+encodeURIComponent(b)};c===b&&(c=f.ajaxSettings.traditional);if(f.isArray(a)||a.jquery&&!f.isPlainObject(a))f.each(a,function(){e(this.name,this.value)});else for(var g in a)ca(g,a[g],c,e);return d.join("&").replace(bD,"+")}}),f.extend({active:0,lastModified:{},etag:{}});var cd=f.now(),ce=/(\=)\?(&|$)|\?\?/i;f.ajaxSetup({jsonp:"callback",jsonpCallback:function(){return f.expando+"_"+cd++}}),f.ajaxPrefilter("json jsonp",function(b,c,d){var e=b.contentType==="application/x-www-form-urlencoded"&&typeof b.data=="string";if(b.dataTypes[0]==="jsonp"||b.jsonp!==!1&&(ce.test(b.url)||e&&ce.test(b.data))){var g,h=b.jsonpCallback=f.isFunction(b.jsonpCallback)?b.jsonpCallback():b.jsonpCallback,i=a[h],j=b.url,k=b.data,l="$1"+h+"$2";b.jsonp!==!1&&(j=j.replace(ce,l),b.url===j&&(e&&(k=k.replace(ce,l)),b.data===k&&(j+=(/\?/.test(j)?"&":"?")+b.jsonp+"="+h))),b.url=j,b.data=k,a[h]=function(a){g=[a]},d.always(function(){a[h]=i,g&&f.isFunction(i)&&a[h](g[0])}),b.converters["script json"]=function(){g||f.error(h+" was not called");return g[0]},b.dataTypes[0]="json";return"script"}}),f.ajaxSetup({accepts:{script:"text/javascript, application/javascript, application/ecmascript, application/x-ecmascript"},contents:{script:/javascript|ecmascript/},converters:{"text script":function(a){f.globalEval(a);return a}}}),f.ajaxPrefilter("script",function(a){a.cache===b&&(a.cache=!1),a.crossDomain&&(a.type="GET",a.global=!1)}),f.ajaxTransport("script",function(a){if(a.crossDomain){var d,e=c.head||c.getElementsByTagName("head")[0]||c.documentElement;return{send:function(f,g){d=c.createElement("script"),d.async="async",a.scriptCharset&&(d.charset=a.scriptCharset),d.src=a.url,d.onload=d.onreadystatechange=function(a,c){if(c||!d.readyState||/loaded|complete/.test(d.readyState))d.onload=d.onreadystatechange=null,e&&d.parentNode&&e.removeChild(d),d=b,c||g(200,"success")},e.insertBefore(d,e.firstChild)},abort:function(){d&&d.onload(0,1)}}}});var cf=a.ActiveXObject?function(){for(var a in ch)ch[a](0,1)}:!1,cg=0,ch;f.ajaxSettings.xhr=a.ActiveXObject?function(){return!this.isLocal&&ci()||cj()}:ci,function(a){f.extend(f.support,{ajax:!!a,cors:!!a&&"withCredentials"in a})}(f.ajaxSettings.xhr()),f.support.ajax&&f.ajaxTransport(function(c){if(!c.crossDomain||f.support.cors){var d;return{send:function(e,g){var h=c.xhr(),i,j;c.username?h.open(c.type,c.url,c.async,c.username,c.password):h.open(c.type,c.url,c.async);if(c.xhrFields)for(j in c.xhrFields)h[j]=c.xhrFields[j];c.mimeType&&h.overrideMimeType&&h.overrideMimeType(c.mimeType),!c.crossDomain&&!e["X-Requested-With"]&&(e["X-Requested-With"]="XMLHttpRequest");try{for(j in e)h.setRequestHeader(j,e[j])}catch(k){}h.send(c.hasContent&&c.data||null),d=function(a,e){var j,k,l,m,n;try{if(d&&(e||h.readyState===4)){d=b,i&&(h.onreadystatechange=f.noop,cf&&delete ch[i]);if(e)h.readyState!==4&&h.abort();else{j=h.status,l=h.getAllResponseHeaders(),m={},n=h.responseXML,n&&n.documentElement&&(m.xml=n),m.text=h.responseText;try{k=h.statusText}catch(o){k=""}!j&&c.isLocal&&!c.crossDomain?j=m.text?200:404:j===1223&&(j=204)}}}catch(p){e||g(-1,p)}m&&g(j,k,m,l)},!c.async||h.readyState===4?d():(i=++cg,cf&&(ch||(ch={},f(a).unload(cf)),ch[i]=d),h.onreadystatechange=d)},abort:function(){d&&d(0,1)}}}});var ck={},cl,cm,cn=/^(?:toggle|show|hide)$/,co=/^([+\-]=)?([\d+.\-]+)([a-z%]*)$/i,cp,cq=[["height","marginTop","marginBottom","paddingTop","paddingBottom"],["width","marginLeft","marginRight","paddingLeft","paddingRight"],["opacity"]],cr;f.fn.extend({show:function(a,b,c){var d,e;if(a||a===0)return this.animate(cu("show",3),a,b,c);for(var g=0,h=this.length;g<h;g++)d=this[g],d.style&&(e=d.style.display,!f._data(d,"olddisplay")&&e==="none"&&(e=d.style.display=""),e===""&&f.css(d,"display")==="none"&&f._data(d,"olddisplay",cv(d.nodeName)));for(g=0;g<h;g++){d=this[g];if(d.style){e=d.style.display;if(e===""||e==="none")d.style.display=f._data(d,"olddisplay")||""}}return this},hide:function(a,b,c){if(a||a===0)return this.animate(cu("hide",3),a,b,c);var d,e,g=0,h=this.length;for(;g<h;g++)d=this[g],d.style&&(e=f.css(d,"display"),e!=="none"&&!f._data(d,"olddisplay")&&f._data(d,"olddisplay",e));for(g=0;g<h;g++)this[g].style&&(this[g].style.display="none");return this},_toggle:f.fn.toggle,toggle:function(a,b,c){var d=typeof a=="boolean";f.isFunction(a)&&f.isFunction(b)?this._toggle.apply(this,arguments):a==null||d?this.each(function(){var b=d?a:f(this).is(":hidden");f(this)[b?"show":"hide"]()}):this.animate(cu("toggle",3),a,b,c);return this},fadeTo:function(a,b,c,d){return this.filter(":hidden").css("opacity",0).show().end().animate({opacity:b},a,c,d)},animate:function(a,b,c,d){function g(){e.queue===!1&&f._mark(this);var b=f.extend({},e),c=this.nodeType===1,d=c&&f(this).is(":hidden"),g,h,i,j,k,l,m,n,o;b.animatedProperties={};for(i in a){g=f.camelCase(i),i!==g&&(a[g]=a[i],delete a[i]),h=a[g],f.isArray(h)?(b.animatedProperties[g]=h[1],h=a[g]=h[0]):b.animatedProperties[g]=b.specialEasing&&b.specialEasing[g]||b.easing||"swing";if(h==="hide"&&d||h==="show"&&!d)return b.complete.call(this);c&&(g==="height"||g==="width")&&(b.overflow=[this.style.overflow,this.style.overflowX,this.style.overflowY],f.css(this,"display")==="inline"&&f.css(this,"float")==="none"&&(!f.support.inlineBlockNeedsLayout||cv(this.nodeName)==="inline"?this.style.display="inline-block":this.style.zoom=1))}b.overflow!=null&&(this.style.overflow="hidden");for(i in a)j=new f.fx(this,b,i),h=a[i],cn.test(h)?(o=f._data(this,"toggle"+i)||(h==="toggle"?d?"show":"hide":0),o?(f._data(this,"toggle"+i,o==="show"?"hide":"show"),j[o]()):j[h]()):(k=co.exec(h),l=j.cur(),k?(m=parseFloat(k[2]),n=k[3]||(f.cssNumber[i]?"":"px"),n!=="px"&&(f.style(this,i,(m||1)+n),l=(m||1)/j.cur()*l,f.style(this,i,l+n)),k[1]&&(m=(k[1]==="-="?-1:1)*m+l),j.custom(l,m,n)):j.custom(l,h,""));return!0}var e=f.speed(b,c,d);if(f.isEmptyObject(a))return this.each(e.complete,[!1]);a=f.extend({},a);return e.queue===!1?this.each(g):this.queue(e.queue,g)},stop:function(a,c,d){typeof a!="string"&&(d=c,c=a,a=b),c&&a!==!1&&this.queue(a||"fx",[]);return this.each(function(){function h(a,b,c){var e=b[c];f.removeData(a,c,!0),e.stop(d)}var b,c=!1,e=f.timers,g=f._data(this);d||f._unmark(!0,this);if(a==null)for(b in g)g[b]&&g[b].stop&&b.indexOf(".run")===b.length-4&&h(this,g,b);else g[b=a+".run"]&&g[b].stop&&h(this,g,b);for(b=e.length;b--;)e[b].elem===this&&(a==null||e[b].queue===a)&&(d?e[b](!0):e[b].saveState(),c=!0,e.splice(b,1));(!d||!c)&&f.dequeue(this,a)})}}),f.each({slideDown:cu("show",1),slideUp:cu("hide",1),slideToggle:cu("toggle",1),fadeIn:{opacity:"show"},fadeOut:{opacity:"hide"},fadeToggle:{opacity:"toggle"}},function(a,b){f.fn[a]=function(a,c,d){return this.animate(b,a,c,d)}}),f.extend({speed:function(a,b,c){var d=a&&typeof a=="object"?f.extend({},a):{complete:c||!c&&b||f.isFunction(a)&&a,duration:a,easing:c&&b||b&&!f.isFunction(b)&&b};d.duration=f.fx.off?0:typeof d.duration=="number"?d.duration:d.duration in f.fx.speeds?f.fx.speeds[d.duration]:f.fx.speeds._default;if(d.queue==null||d.queue===!0)d.queue="fx";d.old=d.complete,d.complete=function(a){f.isFunction(d.old)&&d.old.call(this),d.queue?f.dequeue(this,d.queue):a!==!1&&f._unmark(this)};return d},easing:{linear:function(a,b,c,d){return c+d*a},swing:function(a,b,c,d){return(-Math.cos(a*Math.PI)/2+.5)*d+c}},timers:[],fx:function(a,b,c){this.options=b,this.elem=a,this.prop=c,b.orig=b.orig||{}}}),f.fx.prototype={update:function(){this.options.step&&this.options.step.call(this.elem,this.now,this),(f.fx.step[this.prop]||f.fx.step._default)(this)},cur:function(){if(this.elem[this.prop]!=null&&(!this.elem.style||this.elem.style[this.prop]==null))return this.elem[this.prop];var a,b=f.css(this.elem,this.prop);return isNaN(a=parseFloat(b))?!b||b==="auto"?0:b:a},custom:function(a,c,d){function h(a){return e.step(a)}var e=this,g=f.fx;this.startTime=cr||cs(),this.end=c,this.now=this.start=a,this.pos=this.state=0,this.unit=d||this.unit||(f.cssNumber[this.prop]?"":"px"),h.queue=this.options.queue,h.elem=this.elem,h.saveState=function(){e.options.hide&&f._data(e.elem,"fxshow"+e.prop)===b&&f._data(e.elem,"fxshow"+e.prop,e.start)},h()&&f.timers.push(h)&&!cp&&(cp=setInterval(g.tick,g.interval))},show:function(){var a=f._data(this.elem,"fxshow"+this.prop);this.options.orig[this.prop]=a||f.style(this.elem,this.prop),this.options.show=!0,a!==b?this.custom(this.cur(),a):this.custom(this.prop==="width"||this.prop==="height"?1:0,this.cur()),f(this.elem).show()},hide:function(){this.options.orig[this.prop]=f._data(this.elem,"fxshow"+this.prop)||f.style(this.elem,this.prop),this.options.hide=!0,this.custom(this.cur(),0)},step:function(a){var b,c,d,e=cr||cs(),g=!0,h=this.elem,i=this.options;if(a||e>=i.duration+this.startTime){this.now=this.end,this.pos=this.state=1,this.update(),i.animatedProperties[this.prop]=!0;for(b in i.animatedProperties)i.animatedProperties[b]!==!0&&(g=!1);if(g){i.overflow!=null&&!f.support.shrinkWrapBlocks&&f.each(["","X","Y"],function(a,b){h.style["overflow"+b]=i.overflow[a]}),i.hide&&f(h).hide();if(i.hide||i.show)for(b in i.animatedProperties)f.style(h,b,i.orig[b]),f.removeData(h,"fxshow"+b,!0),f.removeData(h,"toggle"+b,!0);d=i.complete,d&&(i.complete=!1,d.call(h))}return!1}i.duration==Infinity?this.now=e:(c=e-this.startTime,this.state=c/i.duration,this.pos=f.easing[i.animatedProperties[this.prop]](this.state,c,0,1,i.duration),this.now=this.start+(this.end-this.start)*this.pos),this.update();return!0}},f.extend(f.fx,{tick:function(){var a,b=f.timers,c=0;for(;c<b.length;c++)a=b[c],!a()&&b[c]===a&&b.splice(c--,1);b.length||f.fx.stop()},interval:13,stop:function(){clearInterval(cp),cp=null},speeds:{slow:600,fast:200,_default:400},step:{opacity:function(a){f.style(a.elem,"opacity",a.now)},_default:function(a){a.elem.style&&a.elem.style[a.prop]!=null?a.elem.style[a.prop]=a.now+a.unit:a.elem[a.prop]=a.now}}}),f.each(["width","height"],function(a,b){f.fx.step[b]=function(a){f.style(a.elem,b,Math.max(0,a.now)+a.unit)}}),f.expr&&f.expr.filters&&(f.expr.filters.animated=function(a){return f.grep(f.timers,function(b){return a===b.elem}).length});var cw=/^t(?:able|d|h)$/i,cx=/^(?:body|html)$/i;"getBoundingClientRect"in c.documentElement?f.fn.offset=function(a){var b=this[0],c;if(a)return this.each(function(b){f.offset.setOffset(this,a,b)});if(!b||!b.ownerDocument)return null;if(b===b.ownerDocument.body)return f.offset.bodyOffset(b);try{c=b.getBoundingClientRect()}catch(d){}var e=b.ownerDocument,g=e.documentElement;if(!c||!f.contains(g,b))return c?{top:c.top,left:c.left}:{top:0,left:0};var h=e.body,i=cy(e),j=g.clientTop||h.clientTop||0,k=g.clientLeft||h.clientLeft||0,l=i.pageYOffset||f.support.boxModel&&g.scrollTop||h.scrollTop,m=i.pageXOffset||f.support.boxModel&&g.scrollLeft||h.scrollLeft,n=c.top+l-j,o=c.left+m-k;return{top:n,left:o}}:f.fn.offset=function(a){var b=this[0];if(a)return this.each(function(b){f.offset.setOffset(this,a,b)});if(!b||!b.ownerDocument)return null;if(b===b.ownerDocument.body)return f.offset.bodyOffset(b);var c,d=b.offsetParent,e=b,g=b.ownerDocument,h=g.documentElement,i=g.body,j=g.defaultView,k=j?j.getComputedStyle(b,null):b.currentStyle,l=b.offsetTop,m=b.offsetLeft;while((b=b.parentNode)&&b!==i&&b!==h){if(f.support.fixedPosition&&k.position==="fixed")break;c=j?j.getComputedStyle(b,null):b.currentStyle,l-=b.scrollTop,m-=b.scrollLeft,b===d&&(l+=b.offsetTop,m+=b.offsetLeft,f.support.doesNotAddBorder&&(!f.support.doesAddBorderForTableAndCells||!cw.test(b.nodeName))&&(l+=parseFloat(c.borderTopWidth)||0,m+=parseFloat(c.borderLeftWidth)||0),e=d,d=b.offsetParent),f.support.subtractsBorderForOverflowNotVisible&&c.overflow!=="visible"&&(l+=parseFloat(c.borderTopWidth)||0,m+=parseFloat(c.borderLeftWidth)||0),k=c}if(k.position==="relative"||k.position==="static")l+=i.offsetTop,m+=i.offsetLeft;f.support.fixedPosition&&k.position==="fixed"&&(l+=Math.max(h.scrollTop,i.scrollTop),m+=Math.max(h.scrollLeft,i.scrollLeft));return{top:l,left:m}},f.offset={bodyOffset:function(a){var b=a.offsetTop,c=a.offsetLeft;f.support.doesNotIncludeMarginInBodyOffset&&(b+=parseFloat(f.css(a,"marginTop"))||0,c+=parseFloat(f.css(a,"marginLeft"))||0);return{top:b,left:c}},setOffset:function(a,b,c){var d=f.css(a,"position");d==="static"&&(a.style.position="relative");var e=f(a),g=e.offset(),h=f.css(a,"top"),i=f.css(a,"left"),j=(d==="absolute"||d==="fixed")&&f.inArray("auto",[h,i])>-1,k={},l={},m,n;j?(l=e.position(),m=l.top,n=l.left):(m=parseFloat(h)||0,n=parseFloat(i)||0),f.isFunction(b)&&(b=b.call(a,c,g)),b.top!=null&&(k.top=b.top-g.top+m),b.left!=null&&(k.left=b.left-g.left+n),"using"in b?b.using.call(a,k):e.css(k)}},f.fn.extend({position:function(){if(!this[0])return null;var a=this[0],b=this.offsetParent(),c=this.offset(),d=cx.test(b[0].nodeName)?{top:0,left:0}:b.offset();c.top-=parseFloat(f.css(a,"marginTop"))||0,c.left-=parseFloat(f.css(a,"marginLeft"))||0,d.top+=parseFloat(f.css(b[0],"borderTopWidth"))||0,d.left+=parseFloat(f.css(b[0],"borderLeftWidth"))||0;return{top:c.top-d.top,left:c.left-d.left}},offsetParent:function(){return this.map(function(){var a=this.offsetParent||c.body;while(a&&!cx.test(a.nodeName)&&f.css(a,"position")==="static")a=a.offsetParent;return a})}}),f.each(["Left","Top"],function(a,c){var d="scroll"+c;f.fn[d]=function(c){var e,g;if(c===b){e=this[0];if(!e)return null;g=cy(e);return g?"pageXOffset"in g?g[a?"pageYOffset":"pageXOffset"]:f.support.boxModel&&g.document.documentElement[d]||g.document.body[d]:e[d]}return this.each(function(){g=cy(this),g?g.scrollTo(a?f(g).scrollLeft():c,a?c:f(g).scrollTop()):this[d]=c})}}),f.each(["Height","Width"],function(a,c){var d=c.toLowerCase();f.fn["inner"+c]=function(){var a=this[0];return a?a.style?parseFloat(f.css(a,d,"padding")):this[d]():null},f.fn["outer"+c]=function(a){var b=this[0];return b?b.style?parseFloat(f.css(b,d,a?"margin":"border")):this[d]():null},f.fn[d]=function(a){var e=this[0];if(!e)return a==null?null:this;if(f.isFunction(a))return this.each(function(b){var c=f(this);c[d](a.call(this,b,c[d]()))});if(f.isWindow(e)){var g=e.document.documentElement["client"+c],h=e.document.body;return e.document.compatMode==="CSS1Compat"&&g||h&&h["client"+c]||g}if(e.nodeType===9)return Math.max(e.documentElement["client"+c],e.body["scroll"+c],e.documentElement["scroll"+c],e.body["offset"+c],e.documentElement["offset"+c]);if(a===b){var i=f.css(e,d),j=parseFloat(i);return f.isNumeric(j)?j:i}return this.css(d,typeof a=="string"?a:a+"px")}}),a.jQuery=a.$=f,typeof define=="function"&&define.amd&&define.amd.jQuery&&define("jquery",[],function(){return f})})(window); 
/* http://keith-wood.name/svg.html
   SVG for jQuery v1.4.5.
   Written by Keith Wood (kbwood{at}iinet.com.au) August 2007.
   Dual licensed under the GPL (http://dev.jquery.com/browser/trunk/jquery/GPL-LICENSE.txt) and
   MIT (http://dev.jquery.com/browser/trunk/jquery/MIT-LICENSE.txt) licenses.
   Please attribute the author if you use it. */
(function($){function SVGManager(){this._settings=[];this._extensions=[];this.regional=[];this.regional['']={errorLoadingText:'Error loading',notSupportedText:'This browser does not support SVG'};this.local=this.regional[''];this._uuid=new Date().getTime();this._renesis=detectActiveX('RenesisX.RenesisCtrl')}function detectActiveX(a){try{return!!(window.ActiveXObject&&new ActiveXObject(a))}catch(e){return false}}var q='svgwrapper';$.extend(SVGManager.prototype,{markerClassName:'hasSVG',svgNS:'http://www.w3.org/2000/svg',xlinkNS:'http://www.w3.org/1999/xlink',_wrapperClass:SVGWrapper,_attrNames:{class_:'class',in_:'in',alignmentBaseline:'alignment-baseline',baselineShift:'baseline-shift',clipPath:'clip-path',clipRule:'clip-rule',colorInterpolation:'color-interpolation',colorInterpolationFilters:'color-interpolation-filters',colorRendering:'color-rendering',dominantBaseline:'dominant-baseline',enableBackground:'enable-background',fillOpacity:'fill-opacity',fillRule:'fill-rule',floodColor:'flood-color',floodOpacity:'flood-opacity',fontFamily:'font-family',fontSize:'font-size',fontSizeAdjust:'font-size-adjust',fontStretch:'font-stretch',fontStyle:'font-style',fontVariant:'font-variant',fontWeight:'font-weight',glyphOrientationHorizontal:'glyph-orientation-horizontal',glyphOrientationVertical:'glyph-orientation-vertical',horizAdvX:'horiz-adv-x',horizOriginX:'horiz-origin-x',imageRendering:'image-rendering',letterSpacing:'letter-spacing',lightingColor:'lighting-color',markerEnd:'marker-end',markerMid:'marker-mid',markerStart:'marker-start',stopColor:'stop-color',stopOpacity:'stop-opacity',strikethroughPosition:'strikethrough-position',strikethroughThickness:'strikethrough-thickness',strokeDashArray:'stroke-dasharray',strokeDashOffset:'stroke-dashoffset',strokeLineCap:'stroke-linecap',strokeLineJoin:'stroke-linejoin',strokeMiterLimit:'stroke-miterlimit',strokeOpacity:'stroke-opacity',strokeWidth:'stroke-width',textAnchor:'text-anchor',textDecoration:'text-decoration',textRendering:'text-rendering',underlinePosition:'underline-position',underlineThickness:'underline-thickness',vertAdvY:'vert-adv-y',vertOriginY:'vert-origin-y',wordSpacing:'word-spacing',writingMode:'writing-mode'},_attachSVG:function(a,b){var c=(a.namespaceURI==this.svgNS?a:null);var a=(c?null:a);if($(a||c).hasClass(this.markerClassName)){return}if(typeof b=='string'){b={loadURL:b}}else if(typeof b=='function'){b={onLoad:b}}$(a||c).addClass(this.markerClassName);try{if(!c){c=document.createElementNS(this.svgNS,'svg');c.setAttribute('version','1.1');if(a.clientWidth>0){c.setAttribute('width',a.clientWidth)}if(a.clientHeight>0){c.setAttribute('height',a.clientHeight)}a.appendChild(c)}this._afterLoad(a,c,b||{})}catch(e){if($.browser.msie){if(!a.id){a.id='svg'+(this._uuid++)}this._settings[a.id]=b;a.innerHTML='<embed type="image/svg+xml" width="100%" '+'height="100%" src="'+(b.initPath||'')+'blank.svg" '+'pluginspage="http://www.adobe.com/svg/viewer/install/main.html"/>'}else{a.innerHTML='<p class="svg_error">'+this.local.notSupportedText+'</p>'}}},_registerSVG:function(){for(var i=0;i<document.embeds.length;i++){var a=document.embeds[i].parentNode;if(!$(a).hasClass($.svg.markerClassName)||$.data(a,q)){continue}var b=null;try{b=document.embeds[i].getSVGDocument()}catch(e){setTimeout($.svg._registerSVG,250);return}b=(b?b.documentElement:null);if(b){$.svg._afterLoad(a,b)}}},_afterLoad:function(a,b,c){var c=c||this._settings[a.id];this._settings[a?a.id:'']=null;var d=new this._wrapperClass(b,a);$.data(a||b,q,d);try{if(c.loadURL){d.load(c.loadURL,c)}if(c.settings){d.configure(c.settings)}if(c.onLoad&&!c.loadURL){c.onLoad.apply(a||b,[d])}}catch(e){alert(e)}},_getSVG:function(a){a=(typeof a=='string'?$(a)[0]:(a.jquery?a[0]:a));return $.data(a,q)},_destroySVG:function(a){var b=$(a);if(!b.hasClass(this.markerClassName)){return}b.removeClass(this.markerClassName);if(a.namespaceURI!=this.svgNS){b.empty()}$.removeData(a,q)},addExtension:function(a,b){this._extensions.push([a,b])},isSVGElem:function(a){return(a.nodeType==1&&a.namespaceURI==$.svg.svgNS)}});function SVGWrapper(a,b){this._svg=a;this._container=b;for(var i=0;i<$.svg._extensions.length;i++){var c=$.svg._extensions[i];this[c[0]]=new c[1](this)}}$.extend(SVGWrapper.prototype,{_width:function(){return(this._container?this._container.clientWidth:this._svg.width)},_height:function(){return(this._container?this._container.clientHeight:this._svg.height)},root:function(){return this._svg},configure:function(a,b,c){if(!a.nodeName){c=b;b=a;a=this._svg}if(c){for(var i=a.attributes.length-1;i>=0;i--){var d=a.attributes.item(i);if(!(d.nodeName=='onload'||d.nodeName=='version'||d.nodeName.substring(0,5)=='xmlns')){a.attributes.removeNamedItem(d.nodeName)}}}for(var e in b){a.setAttribute($.svg._attrNames[e]||e,b[e])}return this},getElementById:function(a){return this._svg.ownerDocument.getElementById(a)},change:function(a,b){if(a){for(var c in b){if(b[c]==null){a.removeAttribute($.svg._attrNames[c]||c)}else{a.setAttribute($.svg._attrNames[c]||c,b[c])}}}return this},_args:function(b,c,d){c.splice(0,0,'parent');c.splice(c.length,0,'settings');var e={};var f=0;if(b[0]!=null&&b[0].jquery){b[0]=b[0][0]}if(b[0]!=null&&!(typeof b[0]=='object'&&b[0].nodeName)){e['parent']=null;f=1}for(var i=0;i<b.length;i++){e[c[i+f]]=b[i]}if(d){$.each(d,function(i,a){if(typeof e[a]=='object'){e.settings=e[a];e[a]=null}})}return e},/*title:function(a,b,c){var d=this._args(arguments,['text']);var e=this._makeNode(d.parent,'title',d.settings||{});e.appendChild(this._svg.ownerDocument.createTextNode(d.text));return e},*/describe:function(a,b,c){var d=this._args(arguments,['text']);var e=this._makeNode(d.parent,'desc',d.settings||{});e.appendChild(this._svg.ownerDocument.createTextNode(d.text));return e},defs:function(a,b,c){var d=this._args(arguments,['id'],['id']);return this._makeNode(d.parent,'defs',$.extend((d.id?{id:d.id}:{}),d.settings||{}))},symbol:function(a,b,c,d,e,f,g){var h=this._args(arguments,['id','x1','y1','width','height']);return this._makeNode(h.parent,'symbol',$.extend({id:h.id,viewBox:h.x1+' '+h.y1+' '+h.width+' '+h.height},h.settings||{}))},marker:function(a,b,c,d,e,f,g,h){var i=this._args(arguments,['id','refX','refY','mWidth','mHeight','orient'],['orient']);return this._makeNode(i.parent,'marker',$.extend({id:i.id,refX:i.refX,refY:i.refY,markerWidth:i.mWidth,markerHeight:i.mHeight,orient:i.orient||'auto'},i.settings||{}))},style:function(a,b,c){var d=this._args(arguments,['styles']);var e=this._makeNode(d.parent,'style',$.extend({type:'text/css'},d.settings||{}));e.appendChild(this._svg.ownerDocument.createTextNode(d.styles));if($.browser.opera){$('head').append('<style type="text/css">'+d.styles+'</style>')}return e},script:function(a,b,c,d){var e=this._args(arguments,['script','type'],['type']);var f=this._makeNode(e.parent,'script',$.extend({type:e.type||'text/javascript'},e.settings||{}));f.appendChild(this._svg.ownerDocument.createTextNode(e.script));if(!$.browser.mozilla){$.globalEval(e.script)}return f},linearGradient:function(a,b,c,d,e,f,g,h){var i=this._args(arguments,['id','stops','x1','y1','x2','y2'],['x1']);var j=$.extend({id:i.id},(i.x1!=null?{x1:i.x1,y1:i.y1,x2:i.x2,y2:i.y2}:{}));return this._gradient(i.parent,'linearGradient',$.extend(j,i.settings||{}),i.stops)},radialGradient:function(a,b,c,d,e,r,f,g,h){var i=this._args(arguments,['id','stops','cx','cy','r','fx','fy'],['cx']);var j=$.extend({id:i.id},(i.cx!=null?{cx:i.cx,cy:i.cy,r:i.r,fx:i.fx,fy:i.fy}:{}));return this._gradient(i.parent,'radialGradient',$.extend(j,i.settings||{}),i.stops)},_gradient:function(a,b,c,d){var e=this._makeNode(a,b,c);for(var i=0;i<d.length;i++){var f=d[i];this._makeNode(e,'stop',$.extend({offset:f[0],stopColor:f[1]},(f[2]!=null?{stopOpacity:f[2]}:{})))}return e},pattern:function(a,b,x,y,c,d,e,f,g,h,i){var j=this._args(arguments,['id','x','y','width','height','vx','vy','vwidth','vheight'],['vx']);var k=$.extend({id:j.id,x:j.x,y:j.y,width:j.width,height:j.height},(j.vx!=null?{viewBox:j.vx+' '+j.vy+' '+j.vwidth+' '+j.vheight}:{}));return this._makeNode(j.parent,'pattern',$.extend(k,j.settings||{}))},clipPath:function(a,b,c,d){var e=this._args(arguments,['id','units']);e.units=e.units||'userSpaceOnUse';return this._makeNode(e.parent,'clipPath',$.extend({id:e.id,clipPathUnits:e.units},e.settings||{}))},mask:function(a,b,x,y,c,d,e){var f=this._args(arguments,['id','x','y','width','height']);return this._makeNode(f.parent,'mask',$.extend({id:f.id,x:f.x,y:f.y,width:f.width,height:f.height},f.settings||{}))},createPath:function(){return new SVGPath()},createText:function(){return new SVGText()},svg:function(a,x,y,b,c,d,e,f,g,h){var i=this._args(arguments,['x','y','width','height','vx','vy','vwidth','vheight'],['vx']);var j=$.extend({x:i.x,y:i.y,width:i.width,height:i.height},(i.vx!=null?{viewBox:i.vx+' '+i.vy+' '+i.vwidth+' '+i.vheight}:{}));return this._makeNode(i.parent,'svg',$.extend(j,i.settings||{}))},group:function(a,b,c){var d=this._args(arguments,['id'],['id']);return this._makeNode(d.parent,'g',$.extend({id:d.id},d.settings||{}))},use:function(a,x,y,b,c,d,e){var f=this._args(arguments,['x','y','width','height','ref']);if(typeof f.x=='string'){f.ref=f.x;f.settings=f.y;f.x=f.y=f.width=f.height=null}var g=this._makeNode(f.parent,'use',$.extend({x:f.x,y:f.y,width:f.width,height:f.height},f.settings||{}));g.setAttributeNS($.svg.xlinkNS,'href',f.ref);return g},link:function(a,b,c){var d=this._args(arguments,['ref']);var e=this._makeNode(d.parent,'a',d.settings);e.setAttributeNS($.svg.xlinkNS,'href',d.ref);return e},image:function(a,x,y,b,c,d,e){var f=this._args(arguments,['x','y','width','height','ref']);var g=this._makeNode(f.parent,'image',$.extend({x:f.x,y:f.y,width:f.width,height:f.height},f.settings||{}));g.setAttributeNS($.svg.xlinkNS,'href',f.ref);return g},path:function(a,b,c){var d=this._args(arguments,['path']);return this._makeNode(d.parent,'path',$.extend({d:(d.path.path?d.path.path():d.path)},d.settings||{}))},rect:function(a,x,y,b,c,d,e,f){var g=this._args(arguments,['x','y','width','height','rx','ry'],['rx']);return this._makeNode(g.parent,'rect',$.extend({x:g.x,y:g.y,width:g.width,height:g.height},(g.rx?{rx:g.rx,ry:g.ry}:{}),g.settings||{}))},circle:function(a,b,c,r,d){var e=this._args(arguments,['cx','cy','r']);return this._makeNode(e.parent,'circle',$.extend({cx:e.cx,cy:e.cy,r:e.r},e.settings||{}))},ellipse:function(a,b,c,d,e,f){var g=this._args(arguments,['cx','cy','rx','ry']);return this._makeNode(g.parent,'ellipse',$.extend({cx:g.cx,cy:g.cy,rx:g.rx,ry:g.ry},g.settings||{}))},line:function(a,b,c,d,e,f){var g=this._args(arguments,['x1','y1','x2','y2']);return this._makeNode(g.parent,'line',$.extend({x1:g.x1,y1:g.y1,x2:g.x2,y2:g.y2},g.settings||{}))},polyline:function(a,b,c){var d=this._args(arguments,['points']);return this._poly(d.parent,'polyline',d.points,d.settings)},polygon:function(a,b,c){var d=this._args(arguments,['points']);return this._poly(d.parent,'polygon',d.points,d.settings)},_poly:function(a,b,c,d){var e='';for(var i=0;i<c.length;i++){e+=c[i].join()+' '}return this._makeNode(a,b,$.extend({points:$.trim(e)},d||{}))},text:function(a,x,y,b,c){var d=this._args(arguments,['x','y','value']);if(typeof d.x=='string'&&arguments.length<4){d.value=d.x;d.settings=d.y;d.x=d.y=null}return this._text(d.parent,'text',d.value,$.extend({x:(d.x&&isArray(d.x)?d.x.join(' '):d.x),y:(d.y&&isArray(d.y)?d.y.join(' '):d.y)},d.settings||{}))},textpath:function(a,b,c,d){var e=this._args(arguments,['path','value']);var f=this._text(e.parent,'textPath',e.value,e.settings||{});f.setAttributeNS($.svg.xlinkNS,'href',e.path);return f},_text:function(a,b,c,d){var e=this._makeNode(a,b,d);if(typeof c=='string'){e.appendChild(e.ownerDocument.createTextNode(c))}else{for(var i=0;i<c._parts.length;i++){var f=c._parts[i];if(f[0]=='tspan'){var g=this._makeNode(e,f[0],f[2]);g.appendChild(e.ownerDocument.createTextNode(f[1]));e.appendChild(g)}else if(f[0]=='tref'){var g=this._makeNode(e,f[0],f[2]);g.setAttributeNS($.svg.xlinkNS,'href',f[1]);e.appendChild(g)}else if(f[0]=='textpath'){var h=$.extend({},f[2]);h.href=null;var g=this._makeNode(e,f[0],h);g.setAttributeNS($.svg.xlinkNS,'href',f[2].href);g.appendChild(e.ownerDocument.createTextNode(f[1]));e.appendChild(g)}else{e.appendChild(e.ownerDocument.createTextNode(f[1]))}}}return e},other:function(a,b,c){var d=this._args(arguments,['name']);return this._makeNode(d.parent,d.name,d.settings||{})},_makeNode:function(a,b,c){a=a||this._svg;var d=this._svg.ownerDocument.createElementNS($.svg.svgNS,b);for(var b in c){var e=c[b];if(e!=null&&e!=null&&(typeof e!='string'||e!='')){d.setAttribute($.svg._attrNames[b]||b,e)}}a.appendChild(d);return d},add:function(b,c){var d=this._args((arguments.length==1?[null,b]:arguments),['node']);var f=this;d.parent=d.parent||this._svg;d.node=(d.node.jquery?d.node:$(d.node));try{if($.svg._renesis){throw'Force traversal';}d.parent.appendChild(d.node.cloneNode(true))}catch(e){d.node.each(function(){var a=f._cloneAsSVG(this);if(a){d.parent.appendChild(a)}})}return this},clone:function(b,c){var d=this;var e=this._args((arguments.length==1?[null,b]:arguments),['node']);e.parent=e.parent||this._svg;e.node=(e.node.jquery?e.node:$(e.node));var f=[];e.node.each(function(){var a=d._cloneAsSVG(this);if(a){a.id='';e.parent.appendChild(a);f.push(a)}});return f},_cloneAsSVG:function(a){var b=null;if(a.nodeType==1){b=this._svg.ownerDocument.createElementNS($.svg.svgNS,this._checkName(a.nodeName));for(var i=0;i<a.attributes.length;i++){var c=a.attributes.item(i);if(c.nodeName!='xmlns'&&c.nodeValue){if(c.prefix=='xlink'){b.setAttributeNS($.svg.xlinkNS,c.localName||c.baseName,c.nodeValue)}else{b.setAttribute(this._checkName(c.nodeName),c.nodeValue)}}}for(var i=0;i<a.childNodes.length;i++){var d=this._cloneAsSVG(a.childNodes[i]);if(d){b.appendChild(d)}}}else if(a.nodeType==3){if($.trim(a.nodeValue)){b=this._svg.ownerDocument.createTextNode(a.nodeValue)}}else if(a.nodeType==4){if($.trim(a.nodeValue)){try{b=this._svg.ownerDocument.createCDATASection(a.nodeValue)}catch(e){b=this._svg.ownerDocument.createTextNode(a.nodeValue.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;'))}}}return b},_checkName:function(a){a=(a.substring(0,1)>='A'&&a.substring(0,1)<='Z'?a.toLowerCase():a);return(a.substring(0,4)=='svg:'?a.substring(4):a)},load:function(j,k){k=(typeof k=='boolean'?{addTo:k}:(typeof k=='function'?{onLoad:k}:(typeof k=='string'?{parent:k}:(typeof k=='object'&&k.nodeName?{parent:k}:(typeof k=='object'&&k.jquery?{parent:k}:k||{})))));if(!k.parent&&!k.addTo){this.clear(false)}var l=[this._svg.getAttribute('width'),this._svg.getAttribute('height')];var m=this;var n=function(a){a=$.svg.local.errorLoadingText+': '+a;if(k.onLoad){k.onLoad.apply(m._container||m._svg,[m,a])}else{m.text(null,10,20,a)}};var o=function(a){var b=new ActiveXObject('Microsoft.XMLDOM');b.validateOnParse=false;b.resolveExternals=false;b.async=false;b.loadXML(a);if(b.parseError.errorCode!=0){n(b.parseError.reason);return null}return b};var p=function(a){if(!a){return}if(a.documentElement.nodeName!='svg'){var b=a.getElementsByTagName('parsererror');var c=(b.length?b[0].getElementsByTagName('div'):[]);n(!b.length?'???':(c.length?c[0]:b[0]).firstChild.nodeValue);return}var d=(k.parent?$(k.parent)[0]:m._svg);var f={};for(var i=0;i<a.documentElement.attributes.length;i++){var g=a.documentElement.attributes.item(i);if(!(g.nodeName=='version'||g.nodeName.substring(0,5)=='xmlns')){f[g.nodeName]=g.nodeValue}}m.configure(d,f,!k.parent);var h=a.documentElement.childNodes;for(var i=0;i<h.length;i++){try{if($.svg._renesis){throw'Force traversal';}d.appendChild(m._svg.ownerDocument.importNode(h[i],true));if(h[i].nodeName=='script'){$.globalEval(h[i].textContent)}}catch(e){m.add(d,h[i])}}if(!k.changeSize){m.configure(d,{width:l[0],height:l[1]})}if(k.onLoad){k.onLoad.apply(m._container||m._svg,[m])}};if(j.match('<svg')){p($.browser.msie?o(j):new DOMParser().parseFromString(j,'text/xml'))}else{$.ajax({url:j,dataType:($.browser.msie?'text':'xml'),success:function(a){p($.browser.msie?o(a):a)},error:function(a,b,c){n(b+(c?' '+c.message:''))}})}return this},remove:function(a){a=(a.jquery?a[0]:a);a.parentNode.removeChild(a);return this},clear:function(a){if(a){this.configure({},true)}while(this._svg.firstChild){this._svg.removeChild(this._svg.firstChild)}return this},toSVG:function(a){a=a||this._svg;return(typeof XMLSerializer=='undefined'?this._toSVG(a):new XMLSerializer().serializeToString(a))},_toSVG:function(a){var b='';if(!a){return b}if(a.nodeType==3){b=a.nodeValue}else if(a.nodeType==4){b='<![CDATA['+a.nodeValue+']]>'}else{b='<'+a.nodeName;if(a.attributes){for(var i=0;i<a.attributes.length;i++){var c=a.attributes.item(i);if(!($.trim(c.nodeValue)==''||c.nodeValue.match(/^\[object/)||c.nodeValue.match(/^function/))){b+=' '+(c.namespaceURI==$.svg.xlinkNS?'xlink:':'')+c.nodeName+'="'+c.nodeValue+'"'}}}if(a.firstChild){b+='>';var d=a.firstChild;while(d){b+=this._toSVG(d);d=d.nextSibling}b+='</'+a.nodeName+'>'}else{b+='/>'}}return b}});function SVGPath(){this._path=''}$.extend(SVGPath.prototype,{reset:function(){this._path='';return this},move:function(x,y,a){a=(isArray(x)?y:a);return this._coords((a?'m':'M'),x,y)},line:function(x,y,a){a=(isArray(x)?y:a);return this._coords((a?'l':'L'),x,y)},horiz:function(x,a){this._path+=(a?'h':'H')+(isArray(x)?x.join(' '):x);return this},vert:function(y,a){this._path+=(a?'v':'V')+(isArray(y)?y.join(' '):y);return this},curveC:function(a,b,c,d,x,y,e){e=(isArray(a)?b:e);return this._coords((e?'c':'C'),a,b,c,d,x,y)},smoothC:function(a,b,x,y,c){c=(isArray(a)?b:c);return this._coords((c?'s':'S'),a,b,x,y)},curveQ:function(a,b,x,y,c){c=(isArray(a)?b:c);return this._coords((c?'q':'Q'),a,b,x,y)},smoothQ:function(x,y,a){a=(isArray(x)?y:a);return this._coords((a?'t':'T'),x,y)},_coords:function(a,b,c,d,e,f,g){if(isArray(b)){for(var i=0;i<b.length;i++){var h=b[i];this._path+=(i==0?a:' ')+h[0]+','+h[1]+(h.length<4?'':' '+h[2]+','+h[3]+(h.length<6?'':' '+h[4]+','+h[5]))}}else{this._path+=a+b+','+c+(d==null?'':' '+d+','+e+(f==null?'':' '+f+','+g))}return this},arc:function(a,b,c,d,e,x,y,f){f=(isArray(a)?b:f);this._path+=(f?'a':'A');if(isArray(a)){for(var i=0;i<a.length;i++){var g=a[i];this._path+=(i==0?'':' ')+g[0]+','+g[1]+' '+g[2]+' '+(g[3]?'1':'0')+','+(g[4]?'1':'0')+' '+g[5]+','+g[6]}}else{this._path+=a+','+b+' '+c+' '+(d?'1':'0')+','+(e?'1':'0')+' '+x+','+y}return this},close:function(){this._path+='z';return this},path:function(){return this._path}});SVGPath.prototype.moveTo=SVGPath.prototype.move;SVGPath.prototype.lineTo=SVGPath.prototype.line;SVGPath.prototype.horizTo=SVGPath.prototype.horiz;SVGPath.prototype.vertTo=SVGPath.prototype.vert;SVGPath.prototype.curveCTo=SVGPath.prototype.curveC;SVGPath.prototype.smoothCTo=SVGPath.prototype.smoothC;SVGPath.prototype.curveQTo=SVGPath.prototype.curveQ;SVGPath.prototype.smoothQTo=SVGPath.prototype.smoothQ;SVGPath.prototype.arcTo=SVGPath.prototype.arc;function SVGText(){this._parts=[]}$.extend(SVGText.prototype,{reset:function(){this._parts=[];return this},string:function(a){this._parts[this._parts.length]=['text',a];return this},span:function(a,b){this._parts[this._parts.length]=['tspan',a,b];return this},ref:function(a,b){this._parts[this._parts.length]=['tref',a,b];return this},path:function(a,b,c){this._parts[this._parts.length]=['textpath',b,$.extend({href:a},c||{})];return this}});$.fn.svg=function(a){var b=Array.prototype.slice.call(arguments,1);if(typeof a=='string'&&a=='get'){return $.svg['_'+a+'SVG'].apply($.svg,[this[0]].concat(b))}return this.each(function(){if(typeof a=='string'){$.svg['_'+a+'SVG'].apply($.svg,[this].concat(b))}else{$.svg._attachSVG(this,a||{})}})};function isArray(a){return(a&&a.constructor==Array)}$.svg=new SVGManager()})(jQuery); 
/* http://keith-wood.name/svg.html
   jQuery DOM compatibility for jQuery SVG v1.4.5.
   Written by Keith Wood (kbwood{at}iinet.com.au) April 2009.
   Dual licensed under the GPL (http://dev.jquery.com/browser/trunk/jquery/GPL-LICENSE.txt) and
   MIT (http://dev.jquery.com/browser/trunk/jquery/MIT-LICENSE.txt) licenses.
   Please attribute the author if you use it. */
(function($){$.fn.addClass=function(e){return function(d){d=d||'';return this.each(function(){if($.svg.isSVGElem(this)){var c=this;$.each(d.split(/\s+/),function(i,a){var b=(c.className?c.className.baseVal:c.getAttribute('class'));if($.inArray(a,b.split(/\s+/))==-1){b+=(b?' ':'')+a;(c.className?c.className.baseVal=b:c.setAttribute('class',b))}})}else{e.apply($(this),[d])}})}}($.fn.addClass);$.fn.removeClass=function(e){return function(d){d=d||'';return this.each(function(){if($.svg.isSVGElem(this)){var c=this;$.each(d.split(/\s+/),function(i,a){var b=(c.className?c.className.baseVal:c.getAttribute('class'));b=$.grep(b.split(/\s+/),function(n,i){return n!=a}).join(' ');(c.className?c.className.baseVal=b:c.setAttribute('class',b))})}else{e.apply($(this),[d])}})}}($.fn.removeClass);$.fn.toggleClass=function(c){return function(a,b){return this.each(function(){if($.svg.isSVGElem(this)){if(typeof b!=='boolean'){b=!$(this).hasClass(a)}$(this)[(b?'add':'remove')+'Class'](a)}else{c.apply($(this),[a,b])}})}}($.fn.toggleClass);$.fn.hasClass=function(d){return function(b){b=b||'';var c=false;this.each(function(){if($.svg.isSVGElem(this)){var a=(this.className?this.className.baseVal:this.getAttribute('class')).split(/\s+/);c=($.inArray(b,a)>-1)}else{c=(d.apply($(this),[b]))}return!c});return c}}($.fn.hasClass);$.fn.attr=function(h){return function(b,c,d){if(typeof b==='string'&&c===undefined){var e=h.apply(this,[b]);if(e&&e.baseVal&&e.baseVal.numberOfItems!=null){c='';e=e.baseVal;if(b=='transform'){for(var i=0;i<e.numberOfItems;i++){var f=e.getItem(i);switch(f.type){case 1:c+=' matrix('+f.matrix.a+','+f.matrix.b+','+f.matrix.c+','+f.matrix.d+','+f.matrix.e+','+f.matrix.f+')';break;case 2:c+=' translate('+f.matrix.e+','+f.matrix.f+')';break;case 3:c+=' scale('+f.matrix.a+','+f.matrix.d+')';break;case 4:c+=' rotate('+f.angle+')';break;case 5:c+=' skewX('+f.angle+')';break;case 6:c+=' skewY('+f.angle+')';break}}e=c.substring(1)}else{e=e.getItem(0).valueAsString}}return(e&&e.baseVal?e.baseVal.valueAsString:e)}var g=b;if(typeof b==='string'){g={};g[b]=c}return this.each(function(){if($.svg.isSVGElem(this)){for(var n in g){var a=($.isFunction(g[n])?g[n]():g[n]);(d?this.style[n]=a:this.setAttribute(n,a))}}else{h.apply($(this),[b,c,d])}})}}($.fn.attr);$.fn.removeAttr=function(b){return function(a){return this.each(function(){if($.svg.isSVGElem(this)){(this[a]&&this[a].baseVal?this[a].baseVal.value='':this.setAttribute(a,''))}else{b.apply($(this),[a])}})}}($.fn.removeAttr);$.extend($.cssNumber,{'stopOpacity':true,'strokeMitrelimit':true,'strokeOpacity':true});if($.cssProps){$.css=function(e){return function(a,b,c){var d=(b.match(/^svg.*/)?$(a).attr($.cssProps[b]||b):'');return d||e(a,b,c)}}($.css)}function anySVG(a){for(var i=0;i<a.length;i++){if(a[i].nodeType==1&&a[i].namespaceURI==$.svg.svgNS){return true}}return false}$.expr.relative['+']=function(d){return function(a,b,c){d(a,b,c||anySVG(a))}}($.expr.relative['+']);$.expr.relative['>']=function(d){return function(a,b,c){d(a,b,c||anySVG(a))}}($.expr.relative['>']);$.expr.relative['']=function(d){return function(a,b,c){d(a,b,c||anySVG(a))}}($.expr.relative['']);$.expr.relative['~']=function(d){return function(a,b,c){d(a,b,c||anySVG(a))}}($.expr.relative['~']);$.expr.find.ID=function(d){return function(a,b,c){return($.svg.isSVGElem(b)?[b.ownerDocument.getElementById(a[1])]:d(a,b,c))}}($.expr.find.ID);var j=document.createElement('div');j.appendChild(document.createComment(''));if(j.getElementsByTagName('*').length>0){$.expr.find.TAG=function(a,b){var c=b.getElementsByTagName(a[1]);if(a[1]==='*'){var d=[];for(var i=0;c[i]||c.item(i);i++){if((c[i]||c.item(i)).nodeType===1){d.push(c[i]||c.item(i))}}c=d}return c}}$.expr.preFilter.CLASS=function(a,b,c,d,f,g){a=' '+a[1].replace(/\\/g,'')+' ';if(g){return a}for(var i=0,elem={};elem!=null;i++){elem=b[i];if(!elem){try{elem=b.item(i)}catch(e){}}if(elem){var h=(!$.svg.isSVGElem(elem)?elem.className:(elem.className?elem.className.baseVal:'')||elem.getAttribute('class'));if(f^(h&&(' '+h+' ').indexOf(a)>-1)){if(!c)d.push(elem)}else if(c){b[i]=false}}}return false};$.expr.filter.CLASS=function(a,b){var c=(!$.svg.isSVGElem(a)?a.className:(a.className?a.className.baseVal:a.getAttribute('class')));return(' '+c+' ').indexOf(b)>-1};$.expr.filter.ATTR=function(g){return function(c,d){var e=null;if($.svg.isSVGElem(c)){e=d[1];$.expr.attrHandle[e]=function(a){var b=a.getAttribute(e);return b&&b.baseVal||b}}var f=g(c,d);if(e){$.expr.attrHandle[e]=null}return f}}($.expr.filter.ATTR)})(jQuery); 
/**
This module provides classes for the parsing of a JSON describing
a faust interface and the realization of that interface in SVG.

It also allows for interaction between this interface and a server.

@module Faust Web UI
@main Faust Web UI
**/

/**
Extension of the JavaScript String class.

@class String
@for
@constructor
**/

/**
Formats a string in a pythonic way.  See
http://docs.python.org/2/library/string.html.

@method format
@for String
@param {Array} args The arguments to be inserted into the string.
@return {String} The formatted string.
**/
String.prototype.format = function (args) {
  var str = this;
  return str.replace(String.prototype.format_regex, function(item) {
    var intVal = parseInt(item.substring(1, item.length - 1));
    var replace;
    if (intVal >= 0) {
      replace = args[intVal];
    }
    else if (intVal === -1) {
      replace = "{";
    }
    else if (intVal === -2) {
      replace = "}";
    }
    else {
      replace = "";
    }
    return replace;
  });
}

/**
The regular expression used to find the insertion points
in a string that needs formatting.

@property format_regex
@for String
@type RegExp
**/
String.prototype.format_regex = new RegExp("{-?[0-9]+}", "g");

/**
Extension of the JavaScript Array class.

@class Array
@for
@constructor
**/

/**
Finds the maximum of a numerical array.

@method max
@for Array
@return {Number} The maximum of the array.
**/
Array.prototype.max = function() {
  var max = this[0];
  var len = this.length;
  for (var i = 1; i < len; i++) {
    if (this[i] > max) {
      max = this[i];
    }
  }
  return max;
}

/**
Finds the minimum of a numerical array.

@method min
@for Array
@return {Number} The minimum of the array.
**/
Array.prototype.min = function() {
  var min = this[0];
  var len = this.length;
  for (var i = 1; i < len; i++) {
    if (this[i] < min) {
      min = this[i];
    }
  }
  return min;
}

/**
Finds the sum of a numerical array.

@method sum
@for Array
@return {Number} The sum of the array.
**/
Array.prototype.sum = function() {
  var sum = 0;
  for(var i = 0; i < this.length; i++) {
    sum += this[i];
  }
  return sum;
}

/**
Provides the base class for the creation of a _f4u$t UI.
It functions more like a namespace than an object, so it
does not have a constructer and only contains classes and
static methods.

@class _f4u$t
@static
**/
var _f4u$t = {};

/**
Estimation of text height in layout computations.

@property TEXT_HEIGHT
@for _f4u$t
@type Number
@default 20
**/
_f4u$t.TEXT_HEIGHT = 20;

/**
Padding between text and other objects.

@property TEXT_PADDING
@for _f4u$t
@type Number
@default 10
**/
_f4u$t.TEXT_PADDING = 10;

/**
Width of value boxes.

@property VALUE_BOX_W
@for _f4u$t
@type Number
@default 60
**/
_f4u$t.VALUE_BOX_W = 60;

/**
Height of value boxes.

@property VALUE_BOX_H
@for _f4u$t
@type Number
@default 20
**/
_f4u$t.VALUE_BOX_H = _f4u$t.TEXT_HEIGHT;

/**
Padding between the bottom of the space an object occupies
and its text-box.

@property TEXT_BOX_PADDING
@for _f4u$t
@type Number
@default 3
**/
_f4u$t.TEXT_BOX_PADDING = 3;

// some convenience methods for inheritence

/**
Used as a placeholder to define constructors via
_f4u$t.extend

@method surrogateCtor
@for _f4u$t
@static
**/
_f4u$t.surrogateCtor = function() {}

/**
Used to make one class inherit from another.

@method extend
@for _f4u$t
@static
@param {Object} base The base class to be inherited from.
@param {Object} sub The class doing the inheriting.
**/
_f4u$t.extend = function(base, sub) {
  // Copy the prototype from the base to setup inheritance
  _f4u$t.surrogateCtor.prototype = base.prototype;
  sub.prototype = new _f4u$t.surrogateCtor();
  // Remember the constructor property was set wrong, let's fix it
  sub.prototype.constructor = sub;
}

/**
Identity function.

@method identity
@for _f4u$t
@static
@param {Object} value The value to return
@return {Object} The input value
**/
_f4u$t.identity = function(value) {
  return value;
}

/**
Enum-like constant for the X axis.

@property X_AXIS
@for _f4u$t
@type Number
@default 0
**/
_f4u$t.X_AXIS = 0;

/**
Enum-like constant for the Y axis.

@property Y_AXIS
@for _f4u$t
@type Number
@default 1
**/
_f4u$t.Y_AXIS = 1;

/**
Enum-like constant for no axes left to consult,
used in iterating.

@property NO_AXES
@for _f4u$t
@type Number
@default 2
**/
_f4u$t.NO_AXES = 2;

/**
Enum-like constant for the left side.

@property LEFT
@for _f4u$t
@type Number
@default -1
**/
_f4u$t.LEFT = -1;

/**
Enum-like constant for the right side.

@property RIGHT
@for _f4u$t
@type Number
@default 1
**/
_f4u$t.RIGHT = 1;

/**
Enum-like constant for the up side.

@property UP
@for _f4u$t
@type Number
@default -1
**/
_f4u$t.UP = -1;

/**
Enum-like constant for the down side.

@property DOWN
@for _f4u$t
@type Number
@default 1
**/
_f4u$t.DOWN = 1;
_f4u$t.CENTER = 0;

/**
Representation of none, null, the abyss, the ether, etc..

@property NULL
@for _f4u$t
@default null
**/
_f4u$t.NONE = null;

/**
RGB value of the color black in an array.

@for _f4u$t
@property BLACK
@type Array
@default [0,0,0]
**/
_f4u$t.BLACK = [0,0,0];

/**
RGB value of the color white in an array.

@property WHITE
@for _f4u$t
@type Array
@default [255,255,255]
**/
_f4u$t.WHITE = [255,255,255];

/**
RGB value of the color cyan in an array.

@property CYAN
@for _f4u$t
@type Array
@default [0,255,255]
**/
_f4u$t.CYAN = [0,255,255];

/**
RGB value of the color cyan in an array.

/**
RGB value of the color grey in an array.

@property GREY
@for _f4u$t
@type Array
@default [100,100,100]
**/
_f4u$t.GREY = [100,100,100];

/**
RGB value of the color pink in an array.

@property PINK
@for _f4u$t
@type Array
@default [233,150,122]
**/
_f4u$t.PINK = [233,150,122];

/**
RGB value of the color green in an array.

@property GREEN
@for _f4u$t
@type Array
@default [173,255,47]
**/
_f4u$t.GREEN = [173,255,47];

/**
RGB value of the color kermit in an array.

@property KERMIT
@for _f4u$t
@type Array
@default [47,243,160]
**/
_f4u$t.KERMIT = [47,243,160];

/**
RGB value of the color pale green in an array.

@property PALEGREEN
@for _f4u$t
@type Array
@default [152,251,152]
**/
_f4u$t.PALEGREEN = [152,251,152];

// INTERACTION WITH THE UI

/**
Information about the current objects being
interacted with.  Holds subproperties id, moved
and value.

@property _I
@for _f4u$t
@type Object
@default {}
**/
_f4u$t._I = {};

/**
Id of the current value box interacted with.

@property _N
@for _f4u$t
@type String
@default ""
**/
_f4u$t._N = "";

/*
 * SERVER INTERACTION
 */

/**
Object that pairs paths of objects on the server
with DOM ids.

@property PATHS_TO_IDS
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.PATHS_TO_IDS = {};

_f4u$t.path_to_id = function (path, id) {
  _f4u$t.PATHS_TO_IDS[path] = id;
}

/**
 Rather than using lots of global variables (clutters namespace)
 or using this.attribute (dangerous depending on browser and libraries),
 we use _f4u$t.IDS_TO_ATTRIBUTES to hold all information for faust UI objects.
 That way, the impact on the namespace of the global session as well
 as the objects is minimal.

@property IDS_TO_ATTRIBUTES
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.IDS_TO_ATTRIBUTES = {};

/**
Returns a random, soft, pretty color, represented
as 0-255 RGB values in an array, to act as a background
for layout managers.

@method magic_color
@for _f4u$t
@static
@return {Array} An array of three values, 0-255 for RGB.
**/
_f4u$t.magic_color = function() {
  var r = Math.floor(Math.random() * 100) + 156;
  var g = Math.floor(Math.random() * 100) + 156;
  var b = 530 - r - g;
  var v = [r,g,b];
  v.sort(function() {return 0.5 - Math.random()}) // shuffles
  return v;
}

/**
Returns a random string.

@method rand_string
@for _f4u$t
@static
@param {Number} n (optional) the length of the string to return
@return {String} a random string
**/
_f4u$t.rand_string = function(n)
{
  var text = "";
  var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  if (!n) {
    n = 8;
  }

  for( var i=0; i < n; i++ ) {
    text += possible.charAt(Math.floor(Math.random() * possible.length));
  }
  return text;
}

/**
Returns true if needle is the first part of haystack

@method first_part_matches
@for _f4u$t
@static
@param {String} haystack the string to search
@param {String} needle the search query
@return {Boolean} true if needle is the first part of the haystack
**/
_f4u$t.first_part_matches = function(haystack, needle) {
  return haystack.indexOf(needle) == 0;
}

/**
Removes needle from the head of haystack.

@method remove_from_head_of_string
@for _f4u$t
@static
@param {String} haystack the string to operate on
@param {String} needle remove
@return {String} the modified string without needle
**/
_f4u$t.remove_from_head_of_string = function(haystack, needle) {
  if (_f4u$t.first_part_matches(haystack, needle)) {
    return haystack.substr(needle.length);
  }
}

/**
The bounds for an accelerometer orientation.

@property orientation_bounds
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.orientation_bounds = {
  alpha : [0, 360],
  beta : [-90, 90],
  gamma : [-90, 90]
};

/**
Parses a string into an orientation

@method parse_orientation
@for _f4u$t
@static
@return {Object}
**/
_f4u$t.parse_orientation = function(s) {
  var split = s.toString().split(" ");
  while (split.indexOf("") >= 0) {
    split.splce(split.indexOf(""), 1);
  }
  if (split.length == 0) {
    return {};
  }
  if (['alpha','beta','gamma'].indexOf(split[0]) < 0) {
    return {};
  }
  var itor = {1 : _f4u$t.orientation_bounds[split[0]][0], 2 : _f4u$t.orientation_bounds[split[0]][1] };

  // this loop creates the rest of the array
  for (var i in itor) {
    if (split.length == i) {
      split.push(itor[i]);
    }
    else {
      split[i] = parseFloat(split[i]);
      if (isNaN(split[i])) {
        split[i] = itor[i];
      }
    }
  }

  return {angle : split[0], low : split[1], high : split[2]};
}

/**
Taking an axis _f4u$t.X_AXIS or _f4u$t.Y_AXIS, returns
the opposite axis.

@method other_axis
@for _f4u$t
@static
@param {Number} axis An axis, either _f4u$t.X_AXIS or _f4u$t.Y_AXIS.
@return {Number} The opposite axis.
**/
_f4u$t.other_axis = function(axis) {
  return (axis + 1) % _f4u$t.NO_AXES;
}

/**
Remaps a value in a range to another range.

@method remap
@for _f4u$t
@static
@param {Number} v The value to remap.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum of the new range.
@param {Number} mx1 The maximum of the new range.
@return {Number} The value v remapped to the new range.
**/
_f4u$t.remap = function(v, mn0, mx0, mn1, mx1) {
  var p = 1.0 * (v - mn0) / (mx0 - mn0);
  return p * (mx1 - mn1) + mn1;
}

/**
Bounds a value between two numbers.

@method bound
@for _f4u$t
@static
@param {Number} v The value to bound.
@param {Number} m One side of the bound (either the min or max).
@param {Number} n The other side of the bound (either min or max).
@return {Number} Bounded value, meaning either unchanged or cropped at the min/max.
**/
_f4u$t.bound = function(v,m,n) {
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  if (v < mn) { return mn; }
  if (v > mx) { return mx; }
  return v;
}

/**
Bounds a value between two numbers, avoiding large leaps
from a previous value

@method bound
@for _f4u$t
@static
@param {Number} aval The value to bound.
@param {Number} pval The previous value
@param {Number} l The lower bound
@param {Number} h The upper bound
@return {Number} The value bounded. If the previous value was the upper
bound, we remain on this to avoid large leaps.
**/
_f4u$t.bound_and_avoid_large_leaps = function(aval, pval, l, h, epsilon) {
  if (!epsilon) {
    epsilon = 0;
  }
  if (l > aval) {
    if (Math.abs(pval - h) <= epsilon) {
      return l;
    }
  }

  else if (aval > h) {
    if (Math.abs(pval - l) <= epsilon) {
      return h;
    }
  }

  // if neither of the above are true, free to move by the difference
  else {
    return aval;
  }

  // corner case - we avoid large leaps
  return pval;
}

/**
Quantizes a value between two numbers at a given step.

@method quantize
@for _f4u$t
@static
@param {Number} v The value to quantize.
@param {Number} m One side of the quantizing range (either the min or max).
@param {Number} n The other side of the quantizing range (either min or max).
@param {Number} s The step value to which the number must be quantized.
@return {Number} ov quantized (and bounded if necessary)
**/
_f4u$t.quantize = function(ov,m,n,s) {
  var v = _f4u$t.bound(ov, m, n);
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  out = Math.floor((v - mn) / s + 0.5) * s + mn;
  return _f4u$t.bound(out, m, n);
}

/**
Flips a value at the center of a range.

@method flip
@for _f4u$t
@static
@param {Number} v The value to flip.
@param {Number} m One side of the range (either the min or max).
@param {Number} n The other side of the range (either min or max).
@return {Number} v flipped over the axis at the middle of the given range.
**/
_f4u$t.flip = function(v,m,n) {
  var mn = Math.min(m,n);
  var mx = Math.max(m,n);
  var offset = (mx - mn) / 2.0 + mn;
  return -1.0 * (v - offset) + offset;
}

/**
Remaps a value via _f4u$t.remap and then bounds it in the new
range via _f4u$t.bound.

@method remap_and_bound
@for _f4u$t
@static
@param {Number} v The value to remap and bound.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v remapped and bounded to the new range.
**/
_f4u$t.remap_and_bound = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.bound(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1);
}

/**
Remaps a value via _f4u$t.remap and then quantizes it in the new
range via _f4u$t.quantize.

@method remap_and_quantize
@for _f4u$t
@static
@param {Number} v The value to remap and quantize.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@param {Number} s The step value to which the number must be quantized.
@return {Number} The value v remapped and quantizeed to the new range.
**/
_f4u$t.remap_and_quantize = function(v, mn0, mx0, mn1, mx1, s) {
  return _f4u$t.quantize(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1, s);
}

/**
Remaps a value via _f4u$t.remap and then bounds it in the new
range via _f4u$t.bound and then flips it via _f4u$t.flip.

@method remap_and_bound_and_flip
@for _f4u$t
@static
@param {Number} v The value to remap and bound and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v remapped and bounded and flipped to the new range.
**/
_f4u$t.remap_and_bound_and_flip = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.bound(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1), mn1, mx1);
}

/**
Remaps a value via _f4u$t.remap and then quantizes it in the new
range via _f4u$t.quantize and then flips it via _f4u$t.flip.

@method remap_and_quantize_and_flip
@for _f4u$t
@static
@param {Number} v The value to remap and quantize and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v remapped and quantized and flipped to the new range.
**/
_f4u$t.remap_and_quantize_and_flip = function(v, mn0, mx0, mn1, mx1, s) {
  return _f4u$t.flip(_f4u$t.quantize(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1, s), mn1, mx1);
}

/**
Remaps a value via _f4u$t.remap and then flips it via _f4u$t.flip.

@method remap_and_flip
@for _f4u$t
@static
@param {Number} v The value to remap and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum of the new range.
@param {Number} mx1 The maximum of the new range.
@return {Number} The value v remapped and flipped to the new range.
**/
_f4u$t.remap_and_flip = function(v, mn0, mx0, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.remap(v, mn0, mx0, mn1, mx1), mn1, mx1);
}

/**
Bounds a value via _f4u$t.bound and then flips it via _f4u$t.flip.

@method bound_and_flip
@for _f4u$t
@static
@param {Number} v The value to bound and flip.
@param {Number} mn0 The minimum of the old range.
@param {Number} mx0 The maximum of the old range.
@param {Number} mn1 The minimum and bound of the new range.
@param {Number} mx1 The maximum and bound of the new range.
@return {Number} The value v bounded and and flipped to the new range.
**/
_f4u$t.bound_and_flip = function(v, mn1, mx1) {
  return _f4u$t.flip(_f4u$t.bound(v, mn1, mx1), mn1, mx1);
}

/**
Finds the sign of a number.

@method sign
@for _f4u$t
@static
@param {Number} x The number whose sign we want.
@return {Number} The sign, either -1, 1 or 0.
**/
_f4u$t.sign = function(x) {
  return (x == 0 ? x : Math.floor(Math.abs(x) / x));
}

/**
Chooses left, right, or center of range.

@method linear_combinatin
@for _f4u$t
@static
@param {Number} dir The direction indicating which number to use (left/right/center). Note that up is the same as left and down is the same as right.
@param {Number} v1 The first value of the range.
@param {Number} v2 The second value of the range.
@return {Number} The first value if left, the second value if right, or the center if center.
**/
_f4u$t.linear_combination = function(dir, v1, v2) {
  if (dir == _f4u$t.LEFT) {
    return v1;
  }
  if (dir == _f4u$t.RIGHT) {
    return v2;
  }
  return (v1 + v2) / 2.0;
}

/**
Chooses one of two values depending on the axis.

@method xy
@for _f4u$t
@static
@param {Number} a The axis, _f4u$t.X_AXIS or _f4u$t.Y_AXIS.
@param {Number} x The value to return if a is equal to _f4u$t.X_AXIS.
@param {Number} y The value to return if a is equal to _f4u$t.X_AXIS.
@return {Number} x or y, depending on what a is.
**/
_f4u$t.xy = function(a,x,y) {
  return (a == _f4u$t.X_AXIS ? x : y);
}

/**
Returns the trailing part of an id.  The faust naming convention gives
all DOM ids a unique identifier at the end, called the trailing part, and
this function returns it.

@method unique
@for _f4u$t
@static
@param {String} s An ID string
@return {String} The unique trailing part, if one exists.
**/
_f4u$t.unique = function(s) {
  var spl = s.toString().split("_");
  if (spl.length == 0) {
    return s;
  }
  return spl[spl.length - 1];
}

/**
Returns the type part of an id.  The faust naming convention gives
all DOM ids a type as the second entry. Examples are vslider, hslider,
rbutton.

@method unique
@for _f4u$t
@static
@param {String} s An ID string
@return {String} The unique type, if one exists.
**/
_f4u$t.type = function(s) {
  var spl = s.toString().split("_");
  if (spl.length == 0) {
    console.log("incorrect naming of faust object");
    return s;
  }
  return spl[1];
}

/**
Takes an array of three values (R, G, and B) and returns a color
useable by CSS.

@method color_to_css
@for _f4u$t
@static
@param {Array, String} rgb An array with three values for
R, G, and B or a CSS string to bypass the conversion.
@return {String} An RGB value useable by CSS.
**/
_f4u$t.color_to_rgb = function(rgb) {
  if (typeof rgb == 'string')
    return rgb;
  return (rgb ? "rgb("+rgb[0]+","+rgb[1]+","+rgb[2]+")" : 'none');
}

/**
A function that generates a random 7-letter string.

@method randString
@for _f4u$t
@static
@return {String} A random 7-letter string.
**/
_f4u$t.randString = function() {
  var result = '';
  var length = 7;
  var chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (var i = length; i > 0; --i) {
    result += chars[Math.round(Math.random() * (chars.length - 1))];
  }
  return result;
}

/**
A function that returns either a given value or a default if
the given is null

@method initifnull
@for _f4u$t
@static
@param {any} v The value to use.
@param {any} d The default to return if v is null.
@return {any} Either v or d.
**/
_f4u$t.initifnull = function(v,d) {
  return (v == null ? d : v);
}

// TRIGONOMETRIC FUNCTIONS

/**
In a range, find all angles that fall at a multiple of 90 degrees.

@method find_all_90s
@for _f4u$t
@static
@param {Number} a0 The initial angle in degrees.
@param {Number} sweep The angle to sweep from the initial in degrees.
@return {Array} All multiples of 90 between a0 and a0 + sweep inclusive.
**/
_f4u$t.find_all_90s = function(a0, sweep) {
  var total = 0;
  var out = [];
  while (a0 > total) {
    total += 90;
  }
  while (total <= a0 + sweep) {
    out.push(total);
    total += 90;
  }
  return out;
}

/**
Given a polar coordiante, find the cartesian point

@method point_from_polar
@for _f4u$t
@static
@param {Number} r Radius.
@param {Number} a Angle in radians.
@return {Array} The cartesian coordinate as [x,y].
**/
_f4u$t.point_from_polar = function(r, a) {
  return [r * Math.cos(a), r * Math.sin(a)];
}

/**
Adds two coordinates in the form [x0,y0] and [x1,y1].

@method coord_sub
@for _f4u$t
@static
@param {Array} c0 First cartesian coordinate.
@param {Array} c1 Second cartesian coordinate.
@return {Array} The sum of the two coordinates.
**/
_f4u$t.coord_add = function(c0, c1) {
  return [c0[0] + c1[0], c0[1] + c1[1]];
}

/**
Subtracts two coordinates in the form [x0,y0] and [x1,y1].

@method coord_sub
@for _f4u$t
@static
@param {Array} c0 First cartesian coordinate.
@param {Array} c1 Second cartesian coordinate, subtracted from first.
@return {Array} The difference of the two coordinates.
**/
_f4u$t.coord_sub = function(c0, c1) {
  return [c0[0] - c1[0], c0[1] - c1[1]];
}

/**
Converts radians to degrees.

@method r2d
@for _f4u$t
@static
@param {Number} Angle in radians.
@return {Number} Angle in degrees.
**/
_f4u$t.r2d = function(a) {
  return a * 180 / Math.PI;
}

/**
Converts degrees to radians.

@method r2d
@for _f4u$t
@static
@param {Number} Angle in degrees.
@return {Number} Angle in radians.
**/
_f4u$t.d2r = function(a) {
  return a * Math.PI / 180.;
}

/**
Ajax queue.

@property ajax_queue
@for _f4u$t
@type Object
@default {}
**/
_f4u$t.ajax_queue = {};

/**
Is the ajax queue busy?

@property ajax_queue_busy
@for _f4u$t
@type Boolean
@default false
**/
_f4u$t.ajax_queue_busy = false;

/**
Active addresses being sent to server.

@property active_addresses
@for _f4u$t
@type Array
@default []
**/
_f4u$t.active_addresses = [];

/**
A box class.

@class Box
@namespace _f4u$t
@constructor
**/

_f4u$t.Box = function() {
  /**
  Resets the x and y of a box to their defaults
  
  @method clear
  @for _f4u$t.Box
  **/
  this.clear = function() {
    /**
    x range of a Box.
    
    @property x
    @for _f4u$t.Box
    @type Array
    @default [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY]
    **/
    this.x = [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY];
    /**
    y range of a Box.
    
    @property y
    @for _f4u$t.Box
    @type Array
    @default [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY]
    **/
    this.y = [Number.POSITIVE_INFINITY, Number.NEGATIVE_INFINITY];
  }
  this.clear();
}

/**
Adds an array of points, with each point in the form [x,y], to the
interior of the box.

@method add_points
@for _f4u$t.Box
@param {Array} pts An array of points.
**/
_f4u$t.Box.prototype.add_points = function(pts) {
  for (var i = 0; i < pts.length; i++) {
    this.add_point(pts[i]);
  }
}

/**
Adds a point in the form [x,y] to the
interior of the box.

@method add_points
@for _f4u$t.Box
@param {Array} pt A point to add.
**/
_f4u$t.Box.prototype.add_point = function(pt) {
  this.x = [Math.min(this.x[0], pt[0]), Math.max(this.x[1], pt[0])];
  this.y = [Math.min(this.y[0], pt[1]), Math.max(this.y[1], pt[1])];
}

/**
Returns the length of the box along the x and y axes.

@method lens
@for _f4u$t.Box
@return {Array} The length of the box along the x and y axes.
**/
_f4u$t.Box.prototype.lens = function(pt) {
  return [this.x[1] - this.x[0], this.y[1] - this.y[0]];
}

/**
Returns the corner points (minima and maxima) of the Box.

@method corners
@for _f4u$t.Box
@return {Array} The corner points of the box.
**/
_f4u$t.Box.prototype.corners = function(pt) {
  return [[this.x[0], this.y[0]], [this.x[1], this.y[1]]];
}

/**
Finds the bounding box of a text node in an svg.

@method get_text_bbox
@for _f4u$t
@param {Object} svg The svg node.
@param {Object} text The text node.
@return {Object} The bounding rectangle of the text node.
**/
_f4u$t.get_text_bbox = function(svg, text, kls) {
  if (!kls) {
    kls = 'faust-label';
  }
  var dummy = _f4u$t.make_text(svg,null,0,0,text, {'class' : kls});
  var bbox = dummy.getBBox();
  _f4u$t.svg_remove(svg, dummy);
  return bbox;
}

_f4u$t.make_rectangle_via_path = function(svg, parent, rf, x, y, w, h, ops) {
  var d = "M{0} {7}L{1} {7}C{2} {7} {2} {7} {2} {3}L{2} {4}C{2} {5} {2} {5} {1} {5}L{0} {5}C{6} {5} {6} {5} {6} {4}L{6} {3}C{6} {7} {6} {7} {0} {7}";
  d = d.format([rf + x, w - rf + x, w + x, rf + y, h - rf + y, h + y, x, y]);
  var rect = _f4u$t.make_path(
    parent,
    d,
    ops
  );

  return rect;
}

/**
Makes the UI for the faust application.

@method make_ui
@for _f4u$t
@param {Object} svg The root SVG node.
@param {Object} raw_json The raw JSON describing the UI to build.
**/
_f4u$t.make_ui = function(svg, raw_json, width, height, hash) {
  var json = eval ("(" + raw_json + ")");
  var faust_svg = new _f4u$t.SVG(
    svg,
    width,
    height,
    {
      constrain : false,
      title : json["ui"][0].label,
      lm : _f4u$t.json_to_ui(json, hash)
    }
  );

  faust_svg.defs();
  faust_svg.lm.mom = faust_svg;
  faust_svg.make();
}

_f4u$t.assign_parameters_to_values = function(URLParams) {
  for (var index in URLParams) {
    var split_index = index.toString().split('.');
    if (split_index.length != 2) {
      continue;
    }
    if (_f4u$t[split_index[0]]) {
      if (_f4u$t[split_index[0]][split_index[1]]) {
        _f4u$t[split_index[0]][split_index[1]] = eval(URLParams[index][URLParams[index].length - 1]);
      }
    }
  }
}

/**
The main function called to build the faust UI.
Parses the URL to include any new documents and then builds the UI.

@method main
@for _f4u$t
@param {Object} raw_json A raw JSON object describing the UI to build.
@param {Object} div (optional) The div to place the object in.
**/
_f4u$t.main = function(raw_json, div, callback) {
    
    if (!div) {
        div = $( "<div />" );
        $("body").append(div);
    }
    // we create a hash for the object
    var hash = $(div).attr('id') ? $(div).attr('id') :  _f4u$t.rand_string(8);
    
    // keep it in the div
    $(div).attr('id', hash);  
    
    // first, we parse URL parameters to change UIs' style if necessary
    var URLParams = _f4u$t.parseURLParams(document.URL);
    // then we assign parameters
    _f4u$t.assign_parameters_to_values(URLParams);
    // we make sure all JS and CSS is loaded before we build the UI
    _f4u$t.load_css_and_then_js(URLParams.css, URLParams.js);
    
    var width = $(div).width();
    if (width == 0) {
        // HUOM: this "- 15" is a kludge and should dealt with more elegantly
        width = $(window).width() - 15;
    }
    var height = $(div).height();
    if (height == 0) {
        // HUOM: this "- 17" is a kludge and should dealt with more elegantly
        height = $(window).height() - 17;
    }
    if (callback) {
        _f4u$t.HANDLER_CALLBACKS.push(function(address, value) {
                                      if (_f4u$t.first_part_matches(address, hash)) {
                                      return callback(_f4u$t.remove_from_head_of_string(address, hash), value);
                                      }
                                      });
    }

    _f4u$t.add_svg_and_onload_to_div(div, raw_json, width, height, hash);

    return function(address, value) {
        return _f4u$t.update_value_at_address(hash+address, value);
    }
}

/**
  Deletes all references to this div in internal data structures, including
  all bindings.  Note that this does NOT delete the div from the page, nor
  does it delete the div's contents.  This is in case the div contains
  other information that the person wants to complete.
  
  To delete the UI in the div, call _f4u$t.hard_delete()
**/
_f4u$t.delete = function(div) {
  var id = $(div).attr('id');
  if (!id) {
    console.log("Can't delete because obj does not exist in the system.");
    return;
  }
  var ids_to_delete = [];
  var keys_to_delete = []
  for (var key in _f4u$t.PATHS_TO_IDS) {
    if (_f4u$t.first_part_matches(key, id)) {
      ids_to_delete.push(_f4u$t.PATHS_TO_IDS[key]);
      keys_to_delete.push(key);
    }
  }
  for (var key_to_delete in keys_to_delete) {
    delete _f4u$t.PATHS_TO_IDS[key_to_delete];
  }
  for (var id_to_delete in ids_to_delete) {
    var slim = _f4u$t.unique(id_to_delete);
    delete _f4u$t.IDS_TO_ATTRIBUTES[slim];
  }
}

_f4u$t.hard_delete = function(div) {
  _f4u$t.delete(div);
  $(div).empty();
}

/**
  To be called when used with the C++/LLVM libfaust based FaustNode.
**/
_f4u$t.make_audio_ui = function(dsp, svg) {
  var json = eval ("(" + dsp.json() + ")");
  var faust_svg = new _f4u$t.SVG(
    svg,
    // kludge to prevent scroll bars...
    $(window).width() - 15,
    // kludge to prevent scroll bars...
    $(window).height() - 17,
    {
      constrain : false,
      title : json["ui"][0].label,
      lm : _f4u$t.json_to_ui(json)
    }
  );
  
  // Keep audio params in a table 
  _f4u$t.controls = new Array();
  for (var i = 0; i < dsp.numberOfAudioParams(); i++) {
    var ctrl = dsp.getAudioParam(i);
    _f4u$t.controls[ctrl.name] = ctrl;
  }
  
  _f4u$t.fausthandler = function(dest, value) {
    _f4u$t.controls[dest].value = value; 
  }
    
  _f4u$t.main_loop = function() {}

  faust_svg.defs();
  faust_svg.lm.mom = faust_svg;
  faust_svg.make();
}

// faust_jquery_svg_backend.js

_f4u$t.make_rectangle_via_rect = function(svg, parent, rf, x, y, w, h, ops) {
  return svg.rect(parent, x, y, w, h, rf, rf, ops);
}

_f4u$t.make_text = function(svg, parent, x, y, text, opts) {
  opts = opts ? opts : {};
  return svg.text(parent,x,y,text,opts);
}

_f4u$t.make_circle = function(svg, parent, cx, cy, radius, opts) {
  opts = opts ? opts : {};
  return svg.circle(parent,cx,cy,radius,opts);
}

_f4u$t.make_g = function(svg, parent, id, opts) {
  opts = opts ? opts : {};
  return svg.group(parent, id, opts);
}

_f4u$t.make_path = function(svg, parent, d, opts) {
  opts = opts ? opts : {};
  return svg.path(parent, d, opts);
}

_f4u$t.make_line = function(svg, parent, x1, y1, x2, y2, opts) {
  opts = opts ? opts : {};
  return svg.line(parent, x1, y1, x2, y2, opts);
}

_f4u$t.configure_svg = function(svg, opts, wipe) {
  svg.configure(opts, wipe ? wipe : false);
}

_f4u$t.get_svg_defs = function(svg) {
  return svg.defs();
}

_f4u$t.make_linear_gradient = function(svg, defs, gradient, stops, x1, y1, x2, y2, opts) {
  opts = opts ? opts : {};
  svg.linearGradient(defs, gradient, stops, x1, y1, x2, y2, opts);
}

_f4u$t.make_radial_gradient = function(svg, defs, gradient, stops, cx, cy, r, fx, fy, opts) {
  opts = opts ? opts : {};
  svg.radialGradient(defs, gradient, stops, cx, cy, r, fx, fy, opts);
}

_f4u$t.svg_remove = function(svg, dummy) {
  svg.remove(dummy);
}

_f4u$t.add_svg_and_onload_to_div = function(div, raw_json, width, height, hash) {
  div.svg({onLoad: function (svg) {
          _f4u$t.make_ui(svg, raw_json, width, height, hash);
          }});
} 
_f4u$t.detect_mobile_device = {
    Android: function() {
        return navigator.userAgent.match(/Android/i);
    },
    BlackBerry: function() {
        return navigator.userAgent.match(/BlackBerry/i);
    },
    iOS: function() {
        return navigator.userAgent.match(/iPhone|iPad|iPod/i);
    },
    Opera: function() {
        return navigator.userAgent.match(/Opera Mini/i);
    },
    Windows: function() {
        return navigator.userAgent.match(/IEMobile/i);
    },
    any: function() {
        return (_f4u$t.detect_mobile_device.Android()
                || _f4u$t.detect_mobile_device.BlackBerry()
                || _f4u$t.detect_mobile_device.iOS()
                || _f4u$t.detect_mobile_device.Opera()
                || _f4u$t.detect_mobile_device.Windows());
    }
};

_f4u$t.disable_zoom = function() {
  var headID = document.getElementsByTagName("head")[0];
  var metaNode = document.createElement('meta');
  metaNode.name = 'viewport';
  metaNode.content = "target-densitydpi=device-dpi, initial-scale=1.0, user-scalable=no";
  headID.appendChild(metaNode);
} 
_f4u$t.checkbox_inits = {
  mom : null,
  d : 19,
  id : null,
  label : '',
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  stretchable : [false, false],
  check_fill : _f4u$t.BLACK,
  check_stroke : _f4u$t.BLACK,
  box_fill : _f4u$t.WHITE,
  box_stroke : _f4u$t.BLACK,
  init : false,
  tooltip : '',
  address : ''
};

_f4u$t.button_inits = {
  mom : null,
  label : '',
  id : null,
  stretchable : [false, false],
  ideal_width : 80,
  ideal_height : 40,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  fill_on : "url(#buttonDownGradient)",
  fill_off : "url(#buttonUpGradient)",
  stroke : _f4u$t.GREY,
  baseline_skip : 5,
  tooltip : '',
  address : ''
};

_f4u$t.tgroup_inits = {
  mom : null,
  headroom : 40,
  headpadding : 10,
  x_padding : 10,
  x_width : 80,
  objs : [],
  init : 0,
  stretchable : [false, false],
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  baseline_skip : 5,
  stroke : 'orange',
  stretchable : [true, true],
  id : null,
  fill_on : "url(#tabGroupDownGradient)",
  fill_off : "url(#tabGroupUpGradient)"
};

_f4u$t.group_inits = {
  mom : null,
  axis : _f4u$t.X_AXIS,
  padding : 10,
  other_axis_padding : 10,
  draw_background : true,
  label : '',
  objs : [],
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  label : '',
  fill : 'url(#groupBoxGradient)',
  stretchable : [false, false],
  stroke : _f4u$t.GREY,
  stretchable : [true, true]
}

_f4u$t.vgroup_inits = $.extend(true, {}, _f4u$t.group_inits);
_f4u$t.hgroup_inits = $.extend(true, {}, _f4u$t.group_inits);

_f4u$t.rbutton_inits = {
  mom : null,
  //ir : 50,
  ir : 30,
  a0 : 135,
  sweep : 270,
  sp : 0.9,
  kp : 0.7,
  id : null,
  label : '',
  unit : null,
  min : 0,
  max : 100,
  init : 50,
  step : 1,
  integer : false,
  ndec : 0,
  stretchable : [false, false],
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  meter_fill : 'rgb(50,50,50)',
  mgroove_fill : 'url(#rotatingButtonMeterGradient)',
  dot_fill : _f4u$t.PINK,
  groove_fill : 'url(#rotatingButtonHandleGradient)',
  handle_fill : 'none',
  mgroove_stroke : _f4u$t.BLACK,
  dot_stroke : _f4u$t.BLACK,
  groove_stroke : _f4u$t.BLACK,
  handle_stroke : _f4u$t.WHITE,
  meter_stroke : _f4u$t.BLACK,
  handle_width : 6,
  tooltip : '',
  address : ''
}

_f4u$t.slidingobject_inits = {
  mom : null,
  id : null,
  axis : _f4u$t.X_AXIS,
  girth : 40,
  length : 175,
  label : '',
  unit : null,
  min : 0,
  max : 100,
  init : 50,
  step : 1,
  integer : false,
  ndec : 0,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  address :  '',
  tooltip : '',
  type : ''
};

_f4u$t.slider_inits = $.extend(true, {}, _f4u$t.slidingobject_inits);
_f4u$t.slider_inits.sp = 30;
_f4u$t.slider_inits.groove_fill = 'red';
_f4u$t.slider_inits.groove_stroke = _f4u$t.BLACK;
_f4u$t.slider_inits.handle_stroke = _f4u$t.BLACK;

_f4u$t.hslider_inits = $.extend(true, {}, _f4u$t.slider_inits);
_f4u$t.hslider_inits.handle_fill = 'url(#horizontalSliderHandleGradient)';
_f4u$t.hslider_inits.meter_fill = 'url(#horizontalSliderMeterGradient)';
_f4u$t.hslider_inits.stretchable = [true, false];
_f4u$t.vslider_inits = $.extend(true, {}, _f4u$t.slider_inits);
_f4u$t.vslider_inits.handle_fill = 'url(#verticalSliderHandleGradient)';
_f4u$t.vslider_inits.meter_fill = 'url(#verticalSliderMeterGradient)';
_f4u$t.vslider_inits.stretchable = [false, true];

_f4u$t.bargraph_inits = $.extend(true, {}, _f4u$t.slidingobject_inits);
_f4u$t.bargraph_inits.curtain_fill = _f4u$t.BLACK;
_f4u$t.bargraph_inits.meter_fill = 'url(#barGraphMeterGradient)';
_f4u$t.bargraph_inits.curtain_stroke = _f4u$t.BLACK;
_f4u$t.bargraph_inits.meter_stroke = _f4u$t.BLACK;
_f4u$t.bargraph_inits.init = null;
_f4u$t.bargraph_inits.girth = 30;

_f4u$t.hbargraph_inits = $.extend(true, {}, _f4u$t.bargraph_inits);
_f4u$t.hbargraph_inits.meter_fill = 'url(#horizontalBarGraphMeterGradient)';
_f4u$t.hbargraph_inits.stretchable = [true, false];
_f4u$t.vbargraph_inits = $.extend(true, {}, _f4u$t.bargraph_inits);
_f4u$t.vbargraph_inits.meter_fill = 'url(#verticalBarGraphMeterGradient)';
_f4u$t.vbargraph_inits.stretchable = [false, true];

_f4u$t.nentry_inits = {
  mom : null,
  id : null,
  ideal_width : _f4u$t.VALUE_BOX_W,
  ideal_height : _f4u$t.VALUE_BOX_H,
  label : '',
  unit : null,
  min : 0,
  max : 100,
  init : 50,
  step : 1,
  integer : false,
  ndec : 0,
  stretchable : [false, false],
  button_fill : _f4u$t.GREY,
  operation_fill : _f4u$t.BLACK,
  button_stroke : _f4u$t.BLACK,
  operation_stroke : _f4u$t.BLACK,
  padding : 1,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  type : 'nentry',
  tooltip : '',
  address : ''
}

_f4u$t.vbox_inits = {
  mom : null,
  id : null,
  width : _f4u$t.VALUE_BOX_W,
  keysink : true,
  height : _f4u$t.VALUE_BOX_H,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  stretchable : [false, false],
  init : 50
}

_f4u$t.label_inits = {
  mom : null,
  label : '',
  id : null,
  gravity : [_f4u$t.CENTER, _f4u$t.CENTER],
  stretchable : [false, false]
}

_f4u$t.linear_gradient_inits = {
  buttonDownGradient :
    {
      stops : [['0%', '#404040', 1],['100%', '#B0B0B0', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  buttonUpGradient :
    {
      stops : [['0%', '#B0B0B0', 1],['100%', '#404040', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  tabGroupDownGradient :
    {
      stops : [['0%', '#404040', 1],['100%', '#B0B0B0', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  tabGroupUpGradient :
    {
      stops : [['0%', '#B0B0B0', 1],['100%', '#404040', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  groupBoxGradient :
    {
      stops : [['0%', '#A0A0A0', 1],['100%', '#202020', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  verticalSliderHandleGradient :
    {
      stops : [['0%', '#AAAAAA', 1], ['5%' ,'#0A0A0A', 1], ['30%','#101010', 1], ['90%','#AAAAAA', 1], ['91%','#000000', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  horizontalSliderHandleGradient :
    {
      stops : [['0%', '#AAAAAA', 1], ['5%' ,'#0A0A0A', 1], ['30%','#101010', 1], ['90%','#AAAAAA', 1], ['91%','#000000', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  rotatingButtonMeterGradient :
    {
      stops : [['0%', 'rgb(255,255,0)', 1], ['100%', 'rgb(255,0,0)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  horizontalSliderMeterGradient :
    {
      stops : [['0%', 'rgb(255,255,0)', 1], ['100%', 'rgb(255,0,0)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  verticalSliderMeterGradient :
    {
      stops : [['0%', 'rgb(255,0,0)', 1], ['100%', 'rgb(255,255,0)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  numericalEntryDownGradient :
    {
      stops : [['0%', '#404040', 1],['100%', '#B0B0B0', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  numericalEntryUpGradient :
    {
      stops : [['0%', '#B0B0B0', 1],['100%', '#404040', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  horizontalBarGraphMeterGradient :
    {
      stops : [['0%', 'rgb(0, 160, 40)', 1], ['50%', 'rgb(0, 160, 40)', 1],
               ['50%', 'rgb(160, 220, 20)', 1], ['60%', 'rgb(160, 220, 20)', 1],
               ['60%', 'rgb(220, 220, 20)', 1], ['70%', 'rgb(220, 220, 20)', 1],
               ['70%', 'rgb(240, 160, 20)', 1], ['80%', 'rgb(240, 160, 20)', 1],
               ['80%', 'rgb(240, 0, 20)', 1], ['100%', 'rgb(240, 0, 20)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "100%",
      y2 : "0%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    },
  verticalBarGraphMeterGradient :
    {
      stops : [['0%', 'rgb(240, 0, 20)', 1], ['20%', 'rgb(240, 0, 20)', 1],
               ['20%', 'rgb(240, 160, 20)', 1], ['30%', 'rgb(240, 160, 20)', 1],
               ['30%', 'rgb(220, 220, 20)', 1], ['40%', 'rgb(220, 220, 20)', 1],
               ['40%', 'rgb(160, 220, 20)', 1], ['50%', 'rgb(160, 220, 20)', 1],
               ['80%', 'rgb(0, 160, 40)', 1], ['100%', 'rgb(0, 160, 40)', 1]],
      x1 : "0%",
      y1 : "0%",
      x2 : "0%",
      y2 : "100%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    }
}

_f4u$t.radial_gradient_inits = {
  rotatingButtonHandleGradient :
    {
      stops : [['0%', 'rgb(255,255,255)', 0.8],['100%', 'rgb(110,110,110)', 1]],
      cx : "40%",
      cy : "35%",
      r : "50%",
      fx : "40%",
      fy : "20%",
      settings : {
        gradientUnits:'objectBoundingBox'
      }
    }
}

_f4u$t.init_prop = function(instance, options, obj, prop) {
  instance[prop] = _f4u$t.initifnull(options[prop], _f4u$t[obj+'_inits'][prop]);
}
 
// FROM http://stackoverflow.com/questions/814613/how-to-read-get-data-from-a-url-using-javascript

_f4u$t.parseURLParams = function(url) {
  //var queryStart = url.indexOf("?") + 1;
  //var queryEnd   = url.indexOf("#") + 1 || url.length + 1;
  var queryStart = url.indexOf("#") + 1;
  var queryEnd   = url.length + 1;
  var query      = url.slice(queryStart, queryEnd - 1);
  var params  = {};

  if (query === url || query === "")
    return params;

  var nvPairs = query.replace(/\+/g, " ").toString().split("&");

  for (var i=0; i<nvPairs.length; i++) {
    var nv = nvPairs[i].toString().split("=");
    var n  = decodeURIComponent(nv[0]);
    var v  = decodeURIComponent(nv[1]);
    if (!(n in params)) {
      params[n] = [];
    }
    params[n].push(nv.length === 2 ? v : null);
  }
  return params;
}

_f4u$t.load_css_and_then_js = function(css, js) {
  if (!css || (css.length == 0)) {
    _f4u$t.load_js(js);
  }
  else {
    var headID = document.getElementsByTagName("head")[0];
    var cssNode = document.createElement('link');
    cssNode.type = 'text/css';
    cssNode.rel = 'stylesheet';
    cssNode.href = css[0];
    cssNode.media = 'screen';
    headID.appendChild(cssNode);
    _f4u$t.load_css_and_then_js(css.slice(1), js);
  }
}

_f4u$t.load_js = function(js) {
  if (!js || (js.length == 0)) {
    return;
  }
  else {
    $.getScript(js[0], function () {
      _f4u$t.load_js(js.slice(1));
    });
  }
}
 
// all onload need to be pushed to the end of the creation

/*
  DEFINES THE FAUST OBJECT CLASS.
  All graphical objects inherit from this.
*/

_f4u$t.UIObject = function() {
  this.x = 0.0;
  this.y = 0.0;
}

_f4u$t.UIObject.prototype.make_group = function(svg, parent, id, opts) {
  opts = opts ? opts : {};
  opts.transform = 'translate('+this.x+','+this.y+')';
  var out = _f4u$t.make_g(
    svg,
    parent,
    id,
    opts);

  return out;
}

_f4u$t.UIObject.prototype.get_x_offset = function() {
  if (!this.mom) {
    return this.x;
  }
  return this.x + this.mom.get_x_offset();
}

_f4u$t.UIObject.prototype.get_y_offset = function() {
  if (!this.mom) {
    return this.y;
  }
  return this.y + this.mom.get_y_offset();
}

_f4u$t.UIObject.prototype.setX = function(x) {
  this.x = x
}

_f4u$t.UIObject.prototype.setY = function(y) {
  this.y = y
}

_f4u$t.UIObject.prototype.do_spacing = function(leaf) { }

_f4u$t.UIObject.prototype.stretch = function(x,y) {
  /*
    the whole family
    all with white hair and canes
    visiting graves
  */
}

_f4u$t.UIObject.prototype.get_root_svg = function() {
  if (!this.mom) {
    return null;
  }
  return (this.mom.svg ? this.mom.svg : this.mom.get_root_svg());
}

_f4u$t.UIObject.prototype.get_root_tooltip_group = function() {
  if (!this.mom) {
    return null;
  }
  return (this.mom.tooltip_group ? this.mom.tooltip_group : this.mom.get_root_tooltip_group());
}

_f4u$t.UIObject.prototype.get_layout_manager = function() {
  if (!this.mom) {
    return null;
  }
  return (this.mom instanceof _f4u$t.LayoutManager ? this.mom : this.mom.get_layout_manager());
}

_f4u$t.UIObject.prototype.make_delayed_tooltips = function(svg) {
  for (var i = 0; i < svg._delayed_tooltip_list.length; i++) {
    svg._delayed_tooltip_list[i][0].make_tooltip(
      svg,
      svg._delayed_tooltip_list[i][1],
      svg._delayed_tooltip_list[i][2]
    );
  }
}

_f4u$t.UIObject.prototype.tooltip_text = function() {
  return this.tooltip;
}

_f4u$t.UIObject.prototype.tooltip_text_dims = function() {
  return _f4u$t.get_text_bbox(this.get_root_svg(), this.tooltip_text());
}

_f4u$t.UIObject.prototype.make_tooltip_text = function(svg, parent, id) {
  var text = this.tooltip_text();
  var full_id = 'faust_tooltip_text_'+id;
  var tttext = _f4u$t.make_text(
    svg,
    parent,
    0,
    0,
    text,
    {
      id: full_id,
      'class': 'faust-tooltip-text'
    }
  );

  return tttext;
}

_f4u$t.UIObject.prototype.make_tooltip_box = function(svg, parent, id) {
  var full_id = 'faust_tooltip_box_'+id;
  var textdims = this.tooltip_text_dims();
  var ttbox = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    2,
    -textdims.width*0.05,
    -(textdims.height*1.1),
    textdims.width*1.1,
    textdims.height*1.3,
    {
      id: full_id,
      fill : _f4u$t.color_to_rgb(_f4u$t.WHITE),
      stroke : _f4u$t.color_to_rgb(_f4u$t.BLACK),
      'class': 'faust-tooltip-box'
    });

  return ttbox;
}

_f4u$t.UIObject.prototype.make_delayed_tooltip = function(obj, svg, linked_obj_id, id) {
  svg._delayed_tooltip_list.push([obj, linked_obj_id, id]);
}

_f4u$t.UIObject.prototype.make_tooltip = function(svg, linked_obj_id, id) {
  if (this.tooltip != "") {
    var full_id = 'faust_tooltip_'+id;
    var root = this.get_root_tooltip_group();
    var g = this.make_group(svg, root, full_id)
    var box = this.make_tooltip_box(svg, g, id);
    var text = this.make_tooltip_text(svg, g, id);
    _f4u$t.move_to_ridiculous_negative(full_id);
    $('#'+linked_obj_id).bind('mouseover', _f4u$t.tooltip_mouseover);
    $('#'+linked_obj_id).bind('mouseout', _f4u$t.tooltip_mouseout);
    return g;
  }
}

// Basic UI objects used all over the place

_f4u$t.ValueBox = function(options) {
  _f4u$t.init_prop(this, options, 'vbox', 'mom');
  _f4u$t.init_prop(this, options, 'vbox', 'init');
  _f4u$t.init_prop(this, options, 'vbox', 'width');
  _f4u$t.init_prop(this, options, 'vbox', 'height');
  _f4u$t.init_prop(this, options, 'vbox', 'keysink');
  _f4u$t.init_prop(this, options, 'vbox', 'gravity');
  _f4u$t.init_prop(this, options, 'vbox', 'id');
  _f4u$t.init_prop(this, options, 'label', 'stretchable');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.ValueBox);

_f4u$t.ValueBox.prototype.dims = function() {
  return [this.width, this.height];
}

_f4u$t.ValueBox.prototype.make_box = function(svg, parent) {
  var id = this.id;
  var mousedown = this.keysink ? '_f4u$t.rotating_button_key_sink("'+id+'")' : '_f4u$t.devnull()';
  var vb = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    2,
    0,
    0,
    this.width,
    this.height,
    {
      id: 'faust_value_box_'+id,
      fill : _f4u$t.color_to_rgb(_f4u$t.WHITE),
      stroke : _f4u$t.color_to_rgb(_f4u$t.BLACK),
      'class': 'faust-vbox-box',
      onmousedown : mousedown,
      ontouchstart : mousedown
    });

  return vb;
}

_f4u$t.ValueBox.prototype.make_value = function(svg, parent) {
  var id = this.id;
  var mousedown = this.keysink ? '_f4u$t.rotating_button_key_sink("'+id+'")' : '_f4u$t.devnull()';
  var vv = _f4u$t.make_text(
    svg,
    parent,
    _f4u$t.xy(this.get_layout_manager().axis, 4, this.width  / 2.0),
    this.height - 4,
    this.init.toString(),
    {
      id: 'faust_value_value_'+id,
      "text-anchor" : _f4u$t.xy(this.get_layout_manager().axis, 'left', 'middle'),
      'class': 'faust-value-text',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );
  return vv;
}

_f4u$t.ValueBox.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id+"_vbox");

  this.make_box(svg, g, id);
  this.make_value(svg, g, id);

  return g;
}

_f4u$t.Label = function(options) {
  _f4u$t.init_prop(this, options, 'label', 'mom');
  _f4u$t.init_prop(this, options, 'label', 'label');
  _f4u$t.init_prop(this, options, 'label', 'id');
  _f4u$t.init_prop(this, options, 'label', 'gravity');
  _f4u$t.init_prop(this, options, 'label', 'stretchable');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.Label);

_f4u$t.Label.prototype.dims = function() {
  var bbx = _f4u$t.get_text_bbox(this.get_root_svg(), this.label);
  return [bbx.width, bbx.height];
}

_f4u$t.Label.prototype.label_text = function() {
  var label = this.label;
  if (this.unit) {/* // deprecated
    label += this.unit;*/
  }
  return label;
}

_f4u$t.Label.prototype.make = function(svg, parent) {
  var id = this.id;

  var label = this.label_text();
  var vl = _f4u$t.make_text(
    svg,
    parent,
    0,
    this.dims()[_f4u$t.Y_AXIS],
    label,
    {
      id: 'faust_label_'+id,
      "class" : "faust-label",
    }
  );

}

/*
  DEFINES THE FAUST INCREMENTAL OBJECT CLASS.
  All objects that go up in increments inherit from this.
*/

_f4u$t.IncrementalObject = function () {}
_f4u$t.extend(_f4u$t.UIObject, _f4u$t.IncrementalObject);

/*
  DEFINES A ROTATING BUTTON.
*/

_f4u$t.RotatingButton = function(options) {
  _f4u$t.init_prop(this, options, 'rbutton', 'mom');
  _f4u$t.init_prop(this, options, 'rbutton', 'ir');
  this._r = this.ir;
  _f4u$t.init_prop(this, options, 'rbutton', 'a0');
  _f4u$t.init_prop(this, options, 'rbutton', 'sweep');
  if (this.sweep < 0) {
    this.a0 += this.sweep;
    this.sweep = Math.abs(this.sweep);
  }
  this.sweep = this.sweep % 360;
  if (this.sweep == 0) {
    this.sweep = 360;
  }
  _f4u$t.init_prop(this, options, 'rbutton', 'sp'); // percentage for white handle
  _f4u$t.init_prop(this, options, 'rbutton', 'kp'); // knob percentage
  _f4u$t.init_prop(this, options, 'rbutton', 'unit');
  _f4u$t.init_prop(this, options, 'rbutton', 'min');
  _f4u$t.init_prop(this, options, 'rbutton', 'max');
  _f4u$t.init_prop(this, options, 'rbutton', 'init');
  _f4u$t.init_prop(this, options, 'rbutton', 'step');
  _f4u$t.init_prop(this, options, 'rbutton', 'integer');
  _f4u$t.init_prop(this, options, 'rbutton', 'ndec');
  _f4u$t.init_prop(this, options, 'rbutton', 'stretchable');
  _f4u$t.init_prop(this, options, 'rbutton', 'orientation');
  _f4u$t.init_prop(this, options, 'rbutton', 'orientation_mode');
  _f4u$t.init_prop(this, options, 'rbutton', 'gravity');
  _f4u$t.init_prop(this, options, 'rbutton', 'mgroove_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'meter_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'groove_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'handle_fill');
  _f4u$t.init_prop(this, options, 'rbutton', 'groove_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'handle_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'mgroove_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'meter_stroke');
  _f4u$t.init_prop(this, options, 'rbutton', 'handle_width');
  _f4u$t.init_prop(this, options, 'rbutton', 'tooltip');
  _f4u$t.init_prop(this, options, 'rbutton', 'address');
  _f4u$t.init_prop(this, options, 'rbutton', 'id');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.RotatingButton);

_f4u$t.RotatingButton.prototype.r = function() {
  return this._r;
}

_f4u$t.RotatingButton.prototype.dims = function() {
  return [this.r() * 2, this.r() * 2];
}


_f4u$t.RotatingButton.prototype.make_mgroove = function(svg, parent, id) {
  var full_id = 'faust_rbutton_mgroove_'+id;
  var mousedown = _f4u$t.activate_rbutton;
  var xo = this.r();
  var yo = this.r();
  var d = "M{0} {1}A{2} {3} 0 {4} {5} {6} {7}L{8} {9}A{10} {11} 0 {12} {13} {14} {15}L{16} {17}";
  d = d.format([
    this.r() * Math.cos(_f4u$t.d2r(this.a0)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(this.a0)) + yo, // outside Y
    this.r(), // radius X
    this.r(), // radius Y
    this.sweep <= 180 ? 0 : 1, // large arc flag
    1, // draw positive
    this.r() * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // endpoint X
    this.r() * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // endpoint Y
    this.r() * this.kp * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // inside endpoint X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // inside endpoint Y
    this.r() * this.kp, // inside radiux X
    this.r() * this.kp, // inside radiux Y
    this.sweep <= 180 ? 0 : 1, // large arc flag
    0, // draw negative
    this.r() * this.kp * Math.cos(_f4u$t.d2r(this.a0)) + xo, // inside X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(this.a0)) + yo, // inside Y
    this.r() * Math.cos(_f4u$t.d2r(this.a0)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(this.a0)) + yo// outside Y
  ]);
  var mgroove = _f4u$t.make_path(
    svg,
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.mgroove_fill),
      stroke : _f4u$t.color_to_rgb(this.mgroove_stroke),
      id : full_id,
      'class' : 'faust-rbutton-mgroove'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return mgroove;
}

_f4u$t.RotatingButton.prototype.make_dot = function(svg, parent, id, rot) {
  var full_id = 'faust_rbutton_dot'+(rot*45)+'_'+id;
  var mousedown = _f4u$t.activate_rbutton;
  var xo = this.r();
  var yo = this.r();
  var dot = _f4u$t.make_circle(
    svg,
    parent,
    this.r() * (this.kp + 1) * 0.5 * Math.cos(_f4u$t.d2r(rot * 45)) + xo,
    this.r() * (this.kp + 1) * 0.5 * Math.sin(_f4u$t.d2r(rot * 45)) + yo,
    this.r() * (1 - this.kp) * 0.5,
    {
      fill : _f4u$t.color_to_rgb(this.dot_fill),
      stroke : _f4u$t.color_to_rgb(this.dot_stroke),
      id : full_id,
      'class' : 'faust-rbutton-dot'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return dot;
}

_f4u$t.RotatingButton.prototype.make_meter = function(svg, parent, id) {
  var full_id = 'faust_rbutton_meter_'+id;
  var mousedown = _f4u$t.activate_rbutton;
  var xo = this.r();
  var yo = this.r();
  var startp = _f4u$t.remap(this.init, this.min, this.max, this.a0, this.a0 + this.sweep);
  var d = "M{0} {1}A{2} {3} 0 {4} {5} {6} {7}L{8} {9}A{10} {11} 0 {12} {13} {14} {15}L{16} {17}";
  d = d.format([
    this.r() * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(startp)) + yo, // outside Y
    this.r(), // radius X
    this.r(), // radius Y
    this.a0 + this.sweep - startp <= 180 ? 0 : 1, // large arc flag
    1, // draw positive
    this.r() * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // endpoint X
    this.r() * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // endpoint Y
    this.r() * this.kp * Math.cos(_f4u$t.d2r(this.a0 + this.sweep)) + xo, // inside endpoint X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(this.a0 + this.sweep)) + yo, // inside endpoint Y
    this.r() * this.kp, // inside radiux X
    this.r() * this.kp, // inside radiux Y
    this.a0 + this.sweep - startp <= 180 ? 0 : 1, // large arc flag
    0, // draw negative
    this.r() * this.kp * Math.cos(_f4u$t.d2r(startp)) + xo, // inside X
    this.r() * this.kp * Math.sin(_f4u$t.d2r(startp)) + yo, // inside Y
    this.r() * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    this.r() * Math.sin(_f4u$t.d2r(startp)) + yo// outside Y
  ]);
  var meter = _f4u$t.make_path(
    svg,
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.meter_fill),
      stroke : _f4u$t.color_to_rgb(this.meter_stroke),
      id : full_id,
      'class' : 'faust-rbutton-meter'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return meter;
}

_f4u$t.RotatingButton.prototype.make_groove = function(svg, parent, id) {
  var mousedown = _f4u$t.activate_rbutton;
  var full_id = 'faust_rbutton_groove_'+id;
  var groove = _f4u$t.make_circle(
    svg,
    parent,
    this.r(),
    this.r(),
    this.r() * this.kp,    
    {
      fill : _f4u$t.color_to_rgb(this.groove_fill),
      stroke : _f4u$t.color_to_rgb(this.groove_stroke),
      id : full_id,
      'class' : 'faust-rbutton-groove'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return groove;
}

_f4u$t.RotatingButton.prototype.make_handle = function(svg, parent, id) {
  var full_id = 'faust_rbutton_handle_'+id;
  var origin = [this.r(), this.r()];
  var startp = _f4u$t.remap(this.init, this.min, this.max, this.a0, this.a0 + this.sweep);
  var mousedown = _f4u$t.activate_rbutton;
  var handle = _f4u$t.make_line(
    svg,
    parent,
    origin[0],
    origin[1],
    origin[0] + (this.r() * this.sp * this.kp) , // set at 0 degrees to start, then rotate below
    origin[1],
    {
      fill : _f4u$t.color_to_rgb(this.handle_fill),
      stroke : _f4u$t.color_to_rgb(this.handle_stroke),
      "stroke-width" : this.handle_width,
      'class' : 'faust-rbutton-handle',
      id : full_id,
      transform : 'translate(0,0) scale(1,1) rotate('+startp+','+origin[0]+','+origin[1]+')'
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return handle;
}

// anchor helps us get correct positioning for rotation
_f4u$t.RotatingButton.prototype.make_anchor = function(svg, parent, id) {
  var origin = [this.r(), this.r()];
  var full_id = 'faust_rbutton_anchor_'+id;

  var anchor = _f4u$t.make_path(
    svg,
    parent,
    "M 0 0L0 1L1 1L1 0L0 0",
    {
      id : full_id,
      style : 'opacity:0.0;',
      transform : 'translate('+origin[0]+','+origin[1]+')',
    }
  );

  return anchor;
}

_f4u$t.RotatingButton.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id);
  _f4u$t.initiate_rbutton(
    id,
    this.a0,
    this.sweep,
    this.r(),
    this.kp,
    this.min,
    this.max,
    this.step,
    this.init,
    this.integer,
    this.ndec,
    this.label,
    this.unit,
    this.orientation,
    this.orientation_mode,
    this.address
  );

  this.make_anchor(svg, g, id);
  if (this.sweep != 360) {
    this.make_mgroove(svg, g, id);
    this.make_meter(svg, g, id);
  } else {
    for (var i = 0; i < 8; i++) {
      this.make_dot(svg, g, id, i);
    }
  }
  this.make_groove(svg, g, id);
  this.make_handle(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

  return g;
}

/*
  DEFINES A SLIDER.
*/

_f4u$t.SlidingObject = function(options, type) {
  _f4u$t.init_prop(this, options, type, 'mom');
  _f4u$t.init_prop(this, options, type, 'axis');
  _f4u$t.init_prop(this, options, type, 'girth');
  _f4u$t.init_prop(this, options, type, 'length');
  _f4u$t.init_prop(this, options, type, 'unit');
  _f4u$t.init_prop(this, options, type, 'min');
  _f4u$t.init_prop(this, options, type, 'max');
  _f4u$t.init_prop(this, options, type, 'init');
  _f4u$t.init_prop(this, options, type, 'step');
  _f4u$t.init_prop(this, options, type, 'integer');
  _f4u$t.init_prop(this, options, type, 'ndec');
  _f4u$t.init_prop(this, options, type, 'stretchable');
  _f4u$t.init_prop(this, options, type, 'gravity');
  _f4u$t.init_prop(this, options, type, 'address');
  _f4u$t.init_prop(this, options, type, 'id');
  _f4u$t.init_prop(this, options, type, 'type');
  _f4u$t.init_prop(this, options, type, 'tooltip');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.SlidingObject);

_f4u$t.SlidingObject.prototype.dims = function() {
  var x = _f4u$t.xy(this.axis, this.length, this.girth);
  var y = _f4u$t.xy(this.axis, this.girth, this.length);
  return [x,y];
}

_f4u$t.SlidingObject.prototype.stretch = function(x,y) {
  if (this.stretchable[this.axis]) {
    dims = this.dims();
    this.length = Math.max(dims[this.axis], _f4u$t.xy(this.axis, x, y));
  }
}

_f4u$t.Slider = function(options, type) {
  _f4u$t.SlidingObject.call(this, options, type);
  _f4u$t.init_prop(this, options, type,'sp');
  _f4u$t.init_prop(this, options, type, 'orientation');
  _f4u$t.init_prop(this, options, type, 'orientation_mode');
  _f4u$t.init_prop(this, options, type, 'groove_fill');
  _f4u$t.init_prop(this, options, type, 'groove_stroke');
  _f4u$t.init_prop(this, options, type, 'handle_fill');
  _f4u$t.init_prop(this, options, type, 'handle_stroke');
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.Slider);

_f4u$t.Slider.prototype.skinny_girth = function() {
  return this.girth * 2.0 / 5.0;
}

_f4u$t.Slider.prototype.make_groove = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.skinny_girth());
  var h = _f4u$t.xy(this.axis, this.skinny_girth(), this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var slider_girth = this.sp;
  var half_slider_girth = slider_girth * 0.5;
  var startp = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0 + half_slider_girth, this.length - half_slider_girth);
  var trans = _f4u$t.xy(this.axis, 'translate(0,'+((this.girth - this.skinny_girth()) / 2)+')', 'translate('+xo+',0)');
  var full_id = 'faust_'+this.type+'_groove_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = _f4u$t[activate_fn];
  var groove = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    _f4u$t.xy(this.axis, startp, 0),
    0,
    _f4u$t.xy(this.axis, w - startp, w),
    _f4u$t.xy(this.axis, h, startp),
    {
      fill : _f4u$t.color_to_rgb(this.groove_fill),
      stroke : _f4u$t.color_to_rgb(this.groove_stroke),
      id : full_id,
      'class' : _f4u$t.xy(this.axis, 'faust-hslider-groove', 'faust-vslider-groove'),
      transform : trans
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return groove;
}

_f4u$t.Slider.prototype.make_meter = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.skinny_girth());
  var h = _f4u$t.xy(this.axis, this.skinny_girth(), this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var trans = _f4u$t.xy(this.axis, 'translate(0,'+((this.girth - this.skinny_girth()) / 2)+')', 'translate('+xo+',0)');
  var full_id = 'faust_'+this.type+'_meter_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = _f4u$t[activate_fn];
  var groove = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.groove_fill),
      stroke : _f4u$t.color_to_rgb(this.groove_stroke),
      id : full_id,
      'class' : _f4u$t.xy(this.axis, 'faust-hslider-meter', 'faust-vslider-meter'),
      transform : trans
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return groove;
}

_f4u$t.Slider.prototype.make_handle = function(svg, parent, id) {
  var dims = this.dims();
  var slider_girth = this.sp;
  var half_slider_girth = slider_girth * 0.5;
  var startp = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0 + half_slider_girth, this.length - half_slider_girth);
  var bottom = startp - half_slider_girth;
  var top = startp + half_slider_girth;
  var w = _f4u$t.xy(this.axis, slider_girth, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, slider_girth);
  var xo = ((this.axis == _f4u$t.Y_AXIS) ? (dims[0] - w) / 2.0 : 0.0);
  var x = _f4u$t.xy(this.axis, bottom, xo);
  var y = _f4u$t.xy(this.axis, 0, bottom);
  var full_id = 'faust_'+this.type+'_handle_'+id;
  var activate_fn = "activate_"+this.type;
  var mousedown = _f4u$t[activate_fn];

  var handle = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.handle_fill),
      stroke : _f4u$t.color_to_rgb(this.handle_stroke),
      id : full_id,
      'class' : _f4u$t.xy(this.axis, 'faust-hslider-handle', 'faust-vslider-handle'),
      transform : 'translate('+x+','+y+')'
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  return handle;
}

_f4u$t.Slider.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id);

  _f4u$t["initiate_"+this.type](
    id,
    this.length,
    this.sp,
    this.min,
    this.max,
    this.step,
    this.init,
    this.integer,
    this.ndec,
    this.label,
    this.unit,
    this.orientation,
    this.orientation_mode,
    this.address
  );

  this.make_meter(svg, g, id);
  this.make_groove(svg, g, id);
  this.make_handle(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);
  return g;
}

/*
  DEFINES A HORIZONTAL SLIDER.
*/

_f4u$t.HorizontalSlider = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.X_AXIS;
  options["type"] = 'hslider';
  _f4u$t.Slider.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.Slider, _f4u$t.HorizontalSlider);

/*
  DEFINES A VERTICAL SLIDER.
*/

_f4u$t.VerticalSlider = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.Y_AXIS;
  options["type"] = 'vslider';
  _f4u$t.Slider.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.Slider, _f4u$t.VerticalSlider);

_f4u$t.BarGraph = function(options, type) {
  _f4u$t.SlidingObject.call(this, options, type);
  this.curtain_fill = _f4u$t.initifnull(options.curtain_fill, _f4u$t.CYAN);
  this.curtain_stroke = _f4u$t.initifnull(options.curtain_stroke, _f4u$t.CYAN);
  this.meter_fill = _f4u$t.initifnull(options.meter_fill, _f4u$t.CYAN);
  this.meter_stroke = _f4u$t.initifnull(options.meter_stroke, _f4u$t.CYAN);
  this.init = this.init ? this.init : this.min;
}

_f4u$t.extend(_f4u$t.SlidingObject, _f4u$t.BarGraph);

_f4u$t.BarGraph.prototype.make_curtain = function(svg, parent, id) {
  var full_id = 'faust_'+this.type+'_curtain_'+id;
  var def = _f4u$t.xy(this.axis, _f4u$t.remap, _f4u$t.remap_and_flip)(this.init, this.min, this.max, 0, this.length);
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, def, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, def);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var curtain = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.curtain_fill),
      stroke : _f4u$t.color_to_rgb(this.curtain_stroke),
      id : full_id,
      transform : _f4u$t.xy(this.axis,'translate('+(xo + this.length)+',0) scale(-1,1)', 'translate('+xo+',0)'),
      'class' : _f4u$t.xy(this.axis, 'faust-hbargraph-curtain', 'faust-vbargraph-curtain')
    });

  return curtain;
}

_f4u$t.BarGraph.prototype.make_meter = function(svg, parent, id) {
  var dims = this.dims();
  var w = _f4u$t.xy(this.axis, this.length, this.girth);
  var h = _f4u$t.xy(this.axis, this.girth, this.length);
  var xo = ((this.axis == _f4u$t.Y_AXIS) || (this instanceof _f4u$t.RotatingButton) ? (dims[0] - w) / 2.0 : 0.0);
  var meter = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.meter_fill),
      stroke : _f4u$t.color_to_rgb(this.meter_stroke),
      id : 'faust_'+this.type+'_meter_'+id,
      transform : 'translate('+xo+',0)',
      'class' : _f4u$t.xy(this.axis, 'faust-hbargraph-meter', 'faust-vbargraph-meter')
    });

  return meter;
}

_f4u$t.BarGraph.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id);

  _f4u$t['initiate_'+this.type](
    id,
    this.girth,
    this.length,
    this.min,
    this.max,
    this.step,
    this.init,
    this.label,
    this.unit,
    this.address
  );

  this.make_meter(svg, g, id);
  this.make_curtain(svg, g, id);

  return g;
}

/*
  DEFINES A HORIZONTAL BAR GRAPH.
*/

_f4u$t.HorizontalBarGraph = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.X_AXIS;
  options["type"] = 'hbargraph';
  _f4u$t.BarGraph.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.BarGraph, _f4u$t.HorizontalBarGraph);

/*
  DEFINES A VERTICAL BAR GRAPH.
*/

_f4u$t.VerticalBarGraph = function(options) {
  options = options || {};
  options["axis"] = _f4u$t.Y_AXIS;
  options["type"] = 'vbargraph';
  _f4u$t.BarGraph.call(this, options, options["type"]);
}

_f4u$t.extend(_f4u$t.BarGraph, _f4u$t.VerticalBarGraph);

_f4u$t.CheckBox = function(options) {
  _f4u$t.init_prop(this, options, 'checkbox','mom');
  _f4u$t.init_prop(this, options, 'checkbox','d');
  _f4u$t.init_prop(this, options, 'checkbox','gravity');
  _f4u$t.init_prop(this, options, 'checkbox','check_fill');
  _f4u$t.init_prop(this, options, 'checkbox','check_stroke');
  _f4u$t.init_prop(this, options, 'checkbox','box_fill');
  _f4u$t.init_prop(this, options, 'checkbox','box_stroke');
  _f4u$t.init_prop(this, options, 'checkbox','init');
  _f4u$t.init_prop(this, options, 'checkbox', 'stretchable');
  _f4u$t.init_prop(this, options, 'checkbox', 'tooltip');
  _f4u$t.init_prop(this, options, 'checkbox','address');
  _f4u$t.init_prop(this, options, 'checkbox', 'id');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.CheckBox);

_f4u$t.CheckBox.prototype.dims = function() {
  return [this.d, this.d];
}

// DON'T FORGET TO SPECIFY CHECK IN CALLBACK
_f4u$t.CheckBox.prototype.make_box = function(svg, parent, id) {
  var full_id = 'faust_checkbox_box_'+id;
  var w = this.d;
  var h = this.d;
  var dims = this.dims();
  var xo = (dims[0] - w) / 2.0;
  var mouseup = '_f4u$t.click_checkbox("'+full_id+'")';
  var touchup = '_f4u$t.touch_checkbox("'+full_id+'")';

  var box = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.box_fill),
      stroke : _f4u$t.color_to_rgb(this.box_stroke),
      id : full_id,
      'class' : 'faust-checkbox-box',
      transform : 'translate('+xo+',0)',
      onmouseup : mouseup,
      ontouchend : touchup
    });

  return box;
}

_f4u$t.CheckBox.prototype.make_check = function(svg, parent, id) {
  var full_id = 'faust_checkbox_check_'+id;
  var w = this.d;
  var h = this.d;
  var dims = this.dims();
  var xo = (dims[0] - w) / 2.0;
  var mouseup = '_f4u$t.change_checkbox("'+full_id+'")';
  //var touchup = '_f4u$t.touch_checkbox("'+full_id+'")';
  var box = _f4u$t.make_path(
    svg,
    parent,
    "M0 0L"+this.d+" "+this.d+"M0 "+this.d+"L"+this.d+" 0",
    {
      id : full_id,
      fill : _f4u$t.color_to_rgb(this.check_fill),
      stroke : _f4u$t.color_to_rgb(this.check_stroke),
      style : "opacity:"+(this.init == 1 ? 1.0 : 0.0),
      onmouseup : mouseup,
      //ontouchend : touchup, // deactivated so that touch doesn't trigger both box and check at the same time
      'class' : 'faust-chekbox-check',
      transform : 'translate('+xo+',0)'
    }
  );

  return box;
}

_f4u$t.CheckBox.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id);

  _f4u$t.initiate_checkbox(id, this.address);

  this.make_box(svg, g, id);
  this.make_check(svg, g, id);
  //this.make_label(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

  return g;
}

/*
  Button in
*/

_f4u$t.Button = function(options) {
  _f4u$t.init_prop(this, options, 'button','mom');
  _f4u$t.init_prop(this, options, 'button','ideal_width');
  _f4u$t.init_prop(this, options, 'button','ideal_height');
  _f4u$t.init_prop(this, options, 'button', 'tooltip');
  _f4u$t.init_prop(this, options, 'button', 'label');
  this._w = this.ideal_width;
  this._h = this.ideal_height;
  _f4u$t.init_prop(this, options, 'button','gravity');
  _f4u$t.init_prop(this, options, 'button','fill_on');
  _f4u$t.init_prop(this, options, 'button','fill_off');
  _f4u$t.init_prop(this, options, 'button','stroke');
  _f4u$t.init_prop(this, options, 'button', 'stretchable');
  _f4u$t.init_prop(this, options, 'button','baseline_skip');
  _f4u$t.init_prop(this, options, 'button', 'id');
  _f4u$t.init_prop(this, options, 'button','address');
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.Button);

_f4u$t.Button.prototype.w = function() {
  return Math.max(this._w,  _f4u$t.get_text_bbox(this.get_root_svg(), this.label).width + 6);
}

_f4u$t.Button.prototype.h = function() {
  return this._h;
}

_f4u$t.Button.prototype.dims = function() {
  return [this.w(), this.h()];
}

_f4u$t.Button.prototype.make_button_box = function(svg, parent, id) {
  var full_id = 'faust_button_box_'+id;
  var rf = 10;
  var button = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    rf,
    0,
    0,
    this.w(),
    this.h(),
    {
      id : full_id,
      fill : _f4u$t.color_to_rgb(this.fill_off),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      'class' : 'faust-button-box',
      onmouseover : '_f4u$t.button_hover("'+full_id+'")',
      onmouseout : '_f4u$t.button_unhover("'+full_id+'")'
    });

  return button;
}

_f4u$t.Button.prototype.make_label = function(svg, parent, id) {
  var vl = _f4u$t.make_text(
    svg,
    parent,
    0,
    0,
    this.label,
    {
      "text-anchor" : 'middle',
      id: 'faust_label_'+id,
      class: 'faust-button-label',
      transform: 'translate('+(this.w() / 2.0)+','+(this.h() / 2.0 + this.baseline_skip)+')',
    }
  );

  return vl;
}

_f4u$t.Button.prototype.make = function(svg, parent) {
  var id = this.id;
  var full_id = 'faust_button_box_'+id;
  var mousedown = '_f4u$t.button_down("'+full_id+'")';
  var mouseup = '_f4u$t.button_up("'+full_id+'")';
  var g = this.make_group(svg, parent, id,
    {
      onmousedown : mousedown,
      //ontouchstart : mousedown,
      onmouseup : mouseup,
      //ontouchend : mouseup
    });

  _f4u$t.initiate_button(
    id,
    _f4u$t.color_to_rgb(this.fill_off),
    _f4u$t.color_to_rgb(this.fill_on),
    this.address
  );

  this.make_button_box(svg, g, id);
  this.make_label(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

  return g;
}

_f4u$t.NumericalEntry = function(options) {
  _f4u$t.init_prop(this, options, 'nentry', 'mom');
  _f4u$t.init_prop(this, options, 'nentry', 'unit');
  _f4u$t.init_prop(this, options, 'nentry', 'ideal_width');
  _f4u$t.init_prop(this, options, 'nentry', 'ideal_height');
  this._w = this.ideal_width;
  this._h = this.ideal_height;
  _f4u$t.init_prop(this, options, 'nentry', 'min');
  _f4u$t.init_prop(this, options, 'nentry', 'max');
  _f4u$t.init_prop(this, options, 'nentry', 'init');
  _f4u$t.init_prop(this, options, 'nentry', 'step');
  _f4u$t.init_prop(this, options, 'nentry', 'integer');
  _f4u$t.init_prop(this, options, 'nentry', 'ndec');
  _f4u$t.init_prop(this, options, 'nentry', 'gravity');
  _f4u$t.init_prop(this, options, 'nentry', 'address');
  _f4u$t.init_prop(this, options, 'nentry', 'id');
  _f4u$t.init_prop(this, options, 'nentry', 'type');
  _f4u$t.init_prop(this, options, 'button', 'stretchable');
  _f4u$t.init_prop(this, options, 'nentry', 'button_fill');
  _f4u$t.init_prop(this, options, 'nentry', 'operation_fill');
  _f4u$t.init_prop(this, options, 'nentry', 'button_stroke');
  _f4u$t.init_prop(this, options, 'nentry', 'operation_stroke');
  _f4u$t.init_prop(this, options, 'nentry', 'padding');
  _f4u$t.init_prop(this, options, 'button', 'tooltip');
}

_f4u$t.extend(_f4u$t.IncrementalObject, _f4u$t.NumericalEntry);

_f4u$t.NumericalEntry.prototype.w = function() {
  return this._w;
}

_f4u$t.NumericalEntry.prototype.h = function() {
  return this._h;
}

_f4u$t.NumericalEntry.prototype.dims = function() {
  return [this.w(), this.h()];
}

_f4u$t.NumericalEntry.prototype.make_left_button = function(svg, parent, id) {
  return this.make_button(svg, parent, id, 0, false);
}

_f4u$t.NumericalEntry.prototype.make_right_button = function(svg, parent, id) {
  return this.make_button(svg, parent, id, this.w() / 2.0 + this.padding, true);
}

_f4u$t.NumericalEntry.prototype.make_button = function(svg, parent, id, xo, incr) {
  var identifier = incr ? 'rbutton' : 'lbutton';
  var tag = incr ? 'plus' : 'minus';
  var full_id = 'faust_nentry_button_'+tag+'_'+id;
  var w = this.w() / 2.0 - this.padding;
  var h = this.h();
  var mousedown = _f4u$t['nentry_down_'+tag]
  var mouseup = _f4u$t['nentry_up_'+tag]
  var button = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      
      fill : _f4u$t.color_to_rgb(this.button_fill),
      stroke : _f4u$t.color_to_rgb(this.button_stroke),
      transform : 'translate('+xo+',0)',
      id : full_id,
      'class' : 'faust-nentry-box'
    });

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  $('#'+full_id).bind('mouseup', mouseup);
  $('#'+full_id).bind('touchend', mouseup);
  return button;
}

_f4u$t.NumericalEntry.prototype.make_minus = function(svg, parent, id) {
  var full_id = 'faust_nentry_minus_'+id;
  var x0 = (this.w() / 2.0 - this.padding) / 4.0;
  var y = this.h() / 2.0;
  var x1 = (this.w() / 2.0 - this.padding) * 3.0 / 4.0;
  var mousedown = _f4u$t.nentry_down_minus;
  var mouseup = _f4u$t.nentry_up_minus;

  var d = "M"+x0+" "+y+"L"+x1+" "+y;
  var minus = _f4u$t.make_path(
    svg,
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.operation_fill),
      stroke : _f4u$t.color_to_rgb(this.operation_stroke),
      id : full_id,
      'class' : 'faust-nentry-operation',
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  $('#'+full_id).bind('mouseup', mouseup);
  $('#'+full_id).bind('touchend', mouseup);
  return minus;
}

_f4u$t.NumericalEntry.prototype.make_plus = function(svg, parent, id) {
  var full_id = 'faust_nentry_plus_'+id;
  var x00 = (this.w() / 2.0 - this.padding) / 4.0;
  var y0 = this.h() / 2.0;
  var x01 = (this.w() / 2.0 - this.padding) * 3.0 / 4.0;
  var x1 = (this.w() / 2.0 - this.padding) / 2.0;
  var y10 = this.h() / 4.0;
  var y11 = this.h() * 3.0 / 4.0;

  var d = "M{0} {1}L{2} {1}M{3} {4}L{3} {5}";
  d = d.format([x00, y0, x01, x1, y10, y11]);
  var mousedown = _f4u$t.nentry_down_plus;
  var mouseup = _f4u$t.nentry_up_plus;

  var plus = _f4u$t.make_path(
    svg,
    parent,
    d,
    {
      fill : _f4u$t.color_to_rgb(this.operation_fill),
      stroke : _f4u$t.color_to_rgb(this.operation_stroke),
      transform : 'translate('+(this.w() / 2.0 + this.padding)+',0)',
      id : full_id,
      'class' : 'faust-nentry-operation',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  $('#'+full_id).bind('mousedown', mousedown);
  $('#'+full_id).bind('touchstart', mousedown);
  $('#'+full_id).bind('mouseup', mouseup);
  $('#'+full_id).bind('touchend', mouseup);
  return plus;
}

_f4u$t.NumericalEntry.prototype.make = function(svg, parent) {
  var id = this.id;
  var g = this.make_group(svg, parent, id);

  _f4u$t.initiate_nentry(
    id,
    this.min,
    this.max,
    this.step,
    this.init,
    this.integer,
    this.ndec,
    this.label,
    this.unit,
    this.address
  );

  this.make_left_button(svg, g, id);
  this.make_right_button(svg, g, id);
  this.make_minus(svg, g, id);
  this.make_plus(svg, g, id);
  this.make_delayed_tooltip(this, svg, id, id);

  return g;
}

_f4u$t.LayoutManager = function(options) {
  var type = _f4u$t.xy(options.axis, 'hgroup','vgroup');
  _f4u$t.init_prop(this, options, type, 'mom');
  _f4u$t.init_prop(this, options, type, 'axis');
  _f4u$t.init_prop(this, options, type, 'padding');
  _f4u$t.init_prop(this, options, type, 'other_axis_padding');
  _f4u$t.init_prop(this, options, type, 'draw_background');
  _f4u$t.init_prop(this, options, type, 'label');
  _f4u$t.init_prop(this, options, type, 'objs');
  _f4u$t.init_prop(this, options, type, 'gravity');
  _f4u$t.init_prop(this, options, type, 'stretchable');
  _f4u$t.init_prop(this, options, type, 'fill');
  _f4u$t.init_prop(this, options, type, 'stroke');
  this.x = 0;
  this.y = 0;
  this.w = 0;
  this.h = 0;
  this.id = _f4u$t.randString();
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.LayoutManager);

_f4u$t.LayoutManager.prototype.dims = function() {
  var outx = [];
  var outy = [];
  for (var i = 0; i < this.objs.length; i++) {
    var dim = this.objs[i].dims();
    outx.push(dim[_f4u$t.X_AXIS]);
    outy.push(dim[_f4u$t.Y_AXIS]);
  }

  var out = [outx, outy];

  for (var i = _f4u$t.X_AXIS; i < _f4u$t.NO_AXES; i++) {
    out[i] = (i == this.axis ? out[i].sum() : out[i].max());
  }

  // this adds in between padding for all objects as well as
  // padding on the top and on the bottom
  out[this.axis] += (this.padding * (this.objs.length + 1));
  // this only adds padding on the sides
  out[_f4u$t.other_axis(this.axis)] += (2 * this.other_axis_padding);
  return out;
}

_f4u$t.LayoutManager.prototype.populate_objects = function() {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].mom = this;
    if ((this.objs[i] instanceof _f4u$t.LayoutManager)
        || (this.objs[i] instanceof _f4u$t.TabGroup)) {
      this.objs[i].populate_objects();
    }
  }
}

_f4u$t.LayoutManager.prototype.stretch = function(x,y) {
  // This function could just do the dim change, but
  // it would leave stuff clumped in the center.  We air
  // things out if nothing stretches.
  if (this.stretchable[this.axis]) {
    var change_padding = true;
    for (var i = 0; i < this.objs.length; i++) {
      if (this.objs[i].stretchable[this.axis]) {
        // if even a single object can be stretched,
        // don't change the padding and let that object stretch
        change_padding = false;
        break;
      }
    }
    if (change_padding) {
      var dim = this.dims();
      // if not a single object can be stretched, then we
      // space objects out via the padding
      this.padding = this.padding + Math.max(0,
                      (_f4u$t.xy(this.axis,x,y)  - dim[this.axis]) / (this.objs.length + 1));
    }
  }

  var dim = this.dims();
  this.dims = function() { return [this.stretchable[_f4u$t.X_AXIS] ? x : dim[_f4u$t.X_AXIS],
                                   this.stretchable[_f4u$t.Y_AXIS] ? y : dim[_f4u$t.Y_AXIS]]; };
}

_f4u$t.LayoutManager.prototype.get_stretchable_coefficient = function(total) {
  var stretchable = 0.0;
  var unstretchable = 0.0;
  for (var i = 0; i < this.objs.length; i++) {
    if (this.objs[i].stretchable[this.axis]) {
      stretchable += this.objs[i].dims()[this.axis];
    } else {
      unstretchable += this.objs[i].dims()[this.axis];
    }
  }
  return (total - (this.padding * (this.objs.length + 1)) - unstretchable) / stretchable;
}

_f4u$t.LayoutManager.prototype.do_spacing = function(leaf) {
  var dims = this.dims();
  var x = dims[_f4u$t.X_AXIS];
  var y = dims[_f4u$t.Y_AXIS];
  this.w = x;
  this.h = y;
  // increase padding by size
  var padding = this.padding;
  // the first padding will need to account for any additional space, thus
  // use this.gravity, as object gravities will be used internally
  var running_count = padding;
  var stretchable_coefficient = this.get_stretchable_coefficient(_f4u$t.xy(this.axis,x,y));
  for (var i = 0; i < this.objs.length; i++) {
    var obj = this.objs[i];
    // the first time we calc the dim, we do it so that we can pass
    // a proposition for stretching to the stretching algorithm
    // the is the maximum space allowable for stretching
    var dim = obj.dims();
    obj.stretch(_f4u$t.xy(this.axis, stretchable_coefficient * dim[_f4u$t.X_AXIS], x - (2 * this.other_axis_padding)), _f4u$t.xy(this.axis, y - (2 * this.other_axis_padding), stretchable_coefficient * dim[_f4u$t.Y_AXIS]));
    // we need to calculate the dimensions a second time
    // because they may have been stretched above
    dim = obj.dims();
    var xv1 = _f4u$t.xy(this.axis, running_count, 0);
    var xv2 = _f4u$t.xy(this.axis, running_count, x - dim[_f4u$t.X_AXIS]);
    obj.setX(_f4u$t.linear_combination(obj.gravity[_f4u$t.X_AXIS], xv1, xv2));
    var yv1 = _f4u$t.xy(this.axis, 0, running_count);
    var yv2 = _f4u$t.xy(this.axis, y - dim[_f4u$t.Y_AXIS], running_count);
    obj.setY(_f4u$t.linear_combination(obj.gravity[_f4u$t.Y_AXIS], yv1, yv2));
    obj.do_spacing(leaf + 1);
    running_count += padding + _f4u$t.xy(this.axis, dim[_f4u$t.X_AXIS], dim[_f4u$t.Y_AXIS]);
  }
}

_f4u$t.LayoutManager.prototype.make_background = function(svg, parent) {
  var full_id = 'faust_background_'+this.id;
  var dims = this.dims();
  var w = dims[0];
  var h = dims[1];
  var background = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      fill : _f4u$t.color_to_rgb(this.fill),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      'class' : 'faust-group-background',
      id : full_id,
      style: +'fill-opacity:0.2;'
    });

  return background;
}

// only for debugging
_f4u$t.LayoutManager.prototype.make_dim_cross = function(svg, parent) {
  var dims = this.dims();
  _f4u$t.make_path(
    svg,
    parent,
    "M0 0L"+dims[0]+' '+dims[1]
  );

  //return background;
}

_f4u$t.LayoutManager.prototype.make = function(svg, parent) {
  var g = this.make_group(svg, parent, this.id);

  if (this.draw_background) {
    this.make_background(svg, g);
  }
  //this.make_label(svg, g);

  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].make(svg, g);
  }

  //this.make_dim_cross(svg, g);
  return g;
}

_f4u$t.TabGroup = function(options) {
  _f4u$t.init_prop(this, options, 'tgroup', 'mom');
  _f4u$t.init_prop(this, options, 'tgroup', 'headroom');
  _f4u$t.init_prop(this, options, 'tgroup', 'headpadding');
  _f4u$t.init_prop(this, options, 'tgroup', 'x_padding');
  _f4u$t.init_prop(this, options, 'tgroup', 'x_width');
  _f4u$t.init_prop(this, options, 'tgroup', 'objs');
  _f4u$t.init_prop(this, options, 'tgroup', 'init');
  _f4u$t.init_prop(this, options, 'tgroup', 'stretchable');
  _f4u$t.init_prop(this, options, 'tgroup', 'gravity');
  _f4u$t.init_prop(this, options, 'tgroup', 'baseline_skip');
  _f4u$t.init_prop(this, options, 'tgroup', 'fill_on');
  _f4u$t.init_prop(this, options, 'tgroup', 'fill_off');
  _f4u$t.init_prop(this, options, 'tgroup', 'stroke');
  this.x = 0;
  this.y = 0;
  this.id = _f4u$t.randString();
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.TabGroup);

_f4u$t.TabGroup.prototype.setX = function(x) {
  this.x = x;
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].x = x;
  }
}

_f4u$t.TabGroup.prototype.setY = function(y) {
  this.y = y;
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].y = y + this.headroom + this.headpadding;
  }
}

_f4u$t.TabGroup.prototype.populate_objects = function() {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].mom = this;
    if ((this.objs[i] instanceof _f4u$t.LayoutManager)
        || (this.objs[i] instanceof _f4u$t.TabGroup)) {
      this.objs[i].populate_objects();
    }
  }
}

_f4u$t.TabGroup.prototype.dims = function() {
  var x = 0;
  var y = 0;
  for (var i = 0; i < this.objs.length; i++) {
    var dim = this.objs[i].dims();
    x = Math.max(x, dim[0]);
    y = Math.max(y, dim[1]);
  }
  return [Math.max(x, (this.x_width + this.x_padding) * this.objs.length - this.x_padding), y + this.headroom + this.headpadding];
}

_f4u$t.TabGroup.prototype.do_spacing = function(leaf) {
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].x = 0;
    this.objs[i].y = this.headroom + this.headpadding;
    this.objs[i].do_spacing(leaf + 1);
  }
}

_f4u$t.TabGroup.prototype.make_label = function(svg, parent, x, y, l, goodid, badidstr) {
  var mousedown = '_f4u$t.activate_tgroup(0,'+(this.headroom + this.headpadding)+',"'+goodid+'","'+badidstr+'")'
  var vl = _f4u$t.make_text(
    svg,
    parent,
    0,
    0,
    l,
    {
      "text-anchor" : 'middle',
      'class' : 'faust-tgroup-label',
      transform : 'translate('+x+','+y+')',
      onmousedown : mousedown,
      ontouchstart : mousedown
    }
  );

  return vl;
}

_f4u$t.TabGroup.prototype.make_tab = function(svg, parent, w, h, x, y, goodid, badidstr, fill, down) {
  var mousedown = '_f4u$t.activate_tgroup(0,'+(this.headroom + this.headpadding)+',"'+goodid+'","'+badidstr+'")';
  var tab = _f4u$t.make_rectangle_via_rect(
    svg,
    parent,
    4,
    0,
    0,
    w,
    h,
    {
      transform: 'translate('+x+','+y+')',
      'class' : 'faust-tgroup-box',
      fill : _f4u$t.color_to_rgb(fill),
      stroke : _f4u$t.color_to_rgb(this.stroke),
      id : 'faust_tab_'+_f4u$t.unique(goodid),
      onmousedown : mousedown,
      ontouchstart : mousedown
    });

  return tab;
}

_f4u$t.TabGroup.prototype.make_tabs = function(svg, parent) {
  // we evenly space buttons across x axis
  // was a bug...
  var g = _f4u$t.make_g(svg, parent, 'faust_tabgroup_tabbar_'+this.id);

  var running_count = 0;
  for (var i = 0; i < this.objs.length; i++) {
    var curobj = this.objs[i];
    var badidstr = this.objs.filter(function(obj) {return obj != curobj}).map(function(obj) {return obj.id;}).join('#');
    this.make_tab(
      svg,
      parent,
      this.x_width,
      this.headroom,
      running_count,
      0,
      curobj.id,
      badidstr,
      this.fill_off,
      i==0);
    this.make_label(
      svg,
      parent,
      running_count + this.x_width / 2.0,
      this.headroom / 2.0 + this.baseline_skip,
      // a bit of a hack...
      curobj.label,
      curobj.id,
      badidstr);
    running_count += this.x_width + this.x_padding;
  }

  return g;
}

_f4u$t.TabGroup.prototype.make = function(svg, parent) {
  var g = this.make_group(svg, parent, this.id);

  this.make_tabs(svg, g);
  for (var i = 0; i < this.objs.length; i++) {
    this.objs[i].make(svg, g);
  }
  // call initiate_tab_group after objects are created
  _f4u$t.initiate_tab_group(this.init, this.objs.map(function(obj) {return obj.id;}).join('#'));

  return g;
}

// rather than extending the jQuery svg object, we just create a wrapper around it
_f4u$t.SVG = function(svg, w, h, options) {
  this.svg = svg;
  this.w = w;
  this.h = h;
  this.lm = _f4u$t.initifnull(options.lm, null);
  this.title = _f4u$t.initifnull(options.title, '');
  this.lm.mom = this;
}

_f4u$t.extend(_f4u$t.UIObject, _f4u$t.SVG);

_f4u$t.SVG.prototype.get_x_offset = function() {
  return 0;
}

_f4u$t.SVG.prototype.get_y_offset = function() {
  return 0;
}

_f4u$t.SVG.prototype.defs = function() {
  for (var gradient in _f4u$t.linear_gradient_inits) {
    _f4u$t.make_linear_gradient(
      this.svg,
      gradient,
      _f4u$t.linear_gradient_inits[gradient]['stops'],
      _f4u$t.linear_gradient_inits[gradient]['x1'],
      _f4u$t.linear_gradient_inits[gradient]['y1'],
      _f4u$t.linear_gradient_inits[gradient]['x2'],
      _f4u$t.linear_gradient_inits[gradient]['y2'],
      _f4u$t.linear_gradient_inits[gradient]['settings']
    );
  }

  for (var gradient in _f4u$t.radial_gradient_inits) {
    _f4u$t.make_radial_gradient(
      this.svg,
      gradient,
      _f4u$t.radial_gradient_inits[gradient]['stops'],
      _f4u$t.radial_gradient_inits[gradient]['cx'],
      _f4u$t.radial_gradient_inits[gradient]['cy'],
      _f4u$t.radial_gradient_inits[gradient]['r'],
      _f4u$t.radial_gradient_inits[gradient]['fx'],
      _f4u$t.radial_gradient_inits[gradient]['fy'],
      _f4u$t.radial_gradient_inits[gradient]['settings']
    );
  }
}

_f4u$t.SVG.prototype.make = function() {
  _f4u$t.configure_svg(
    this.svg,
    {
      width : this.w+'px',
      height : this.h+'px'
    },
    true);
  _f4u$t.ROOT = this.title;
  this.svg._delayed_tooltip_list = [];
  this.lm.populate_objects();
  this.lm.do_spacing(0);
  this.lm.make(this.svg, this.svg);
  this.tooltip_group = _f4u$t.make_g(this.svg, this.svg,'faust_tooltip_group');
  this.make_delayed_tooltips(this.svg);
  // if there is no constrain, the viewport needs to be scaled
  var viewport_dims = this.lm.dims();
  _f4u$t.configure_svg(
    this.svg,
    {
      viewBox: '0 0 '+viewport_dims[0]+' '+viewport_dims[1],
      width : this.w+'px',
      height: this.h+'px',
    },
    true);

  _f4u$t.VIEWPORT_SCALE = Math.min(this.w/viewport_dims[0], this.h/viewport_dims[1]);
}
 
_f4u$t.check_label = function(label) {
  return (label.substring(0, 2) == "0x") ? "" : label;
}

_f4u$t.meta_info = function(dct, prop, def, fn) {
  if (!dct['meta']) {
    return def;
  }
  for (var i=0; i < dct['meta'].length; i++) {
    if (dct['meta'][i][prop]) {
      return fn(dct['meta'][i][prop]);
    }
  }
  return def;
}

_f4u$t.has_knob = function(dct) {
  return _f4u$t.meta_info(dct, 'style', false, function(prop) { return prop == 'knob'; });
}

_f4u$t.get_unit = function(dct) {
  return _f4u$t.meta_info(dct, 'unit', '', _f4u$t.identity);
}

_f4u$t.get_tooltip = function(dct) {
  return _f4u$t.meta_info(dct, 'tooltip', '', _f4u$t.identity);
}

_f4u$t.get_orientation_mode = function(dct) {
  return _f4u$t.meta_info(dct, 'orientation-mode', 'absolute', _f4u$t.identity);
}

_f4u$t.get_orientation = function(dct) {
  return _f4u$t.meta_info(dct, 'orientation', {}, _f4u$t.parse_orientation);
}

_f4u$t.is_panoramic = function(dct) {
  return _f4u$t.meta_info(dct, 'panoramic', false, function(prop) { return prop === 'true'; });
}

_f4u$t.get_sweep = function(dct) {
  return _f4u$t.meta_info(dct, 'sweep', _f4u$t.rbutton_inits.sweep, function(prop) { return parseFloat(prop) != null ? parseFloat(prop) : _f4u$t.rbutton_inits.sweep; });
}

_f4u$t.get_size = function(dct) {
  return _f4u$t.meta_info(dct, 'size', 1, function(prop) { return [0.5,1,2,3,4][parseInt(prop)]; });
}

_f4u$t.getnumspecs = function(dct) {
  var integer = false;
  if((parseFloat(dct["max"]) == parseInt(dct["max"]))
     && (parseFloat(dct["min"]) == parseInt(dct["min"]))
     && (parseFloat(dct["step"]) == parseInt(dct["step"]))
     && (parseFloat(dct["init"]) == parseInt(dct["init"]))
     && !isNaN(dct["max"])
     && !isNaN(dct["min"])
     && !isNaN(dct["step"])
     && !isNaN(dct["init"])) {
    integer = true;
  }

  var maxsplit = dct["max"] ? dct["max"].toString().split('.') : ['',''];
  var minsplit = dct["min"] ? dct["min"].toString().split('.') : ['',''];
  var stepsplit = dct["step"] ? dct["step"].toString().split('.') : ['',''];
  var initsplit = dct["init"] ? dct["init"].toString().split('.') : ['',''];
  maxsplit[1] = maxsplit[1] || '';
  minsplit[1] = minsplit[1] || '';
  stepsplit[1] = stepsplit[1] || '';
  initsplit[1] = initsplit[1] || '';
  parser = integer ? parseInt : parseFloat;
  return {
    min : parser(dct["min"]),
    max : parser(dct["max"]),
    step : parser(dct["step"]),
    init : parser(dct["init"]),
    isint : integer,
    ndec : Math.max(maxsplit[1].length, minsplit[1].length, stepsplit[1].length, initsplit[1].length)
  };
}

_f4u$t.make_rbutton = function(dct, hash) {
  var numspecs = _f4u$t.getnumspecs(dct);
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t.rbutton_inits);
  options.id = id;
  options.min = numspecs["min"];
  options.max = numspecs["max"];
  options.step = numspecs["step"];
  options.init = numspecs["init"];
  options.integer = numspecs["integer"];
  options.ndec = numspecs["ndec"];
  options.address = hash+dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  options.orientation = _f4u$t.get_orientation(dct);
  options.orientation_mode = _f4u$t.get_orientation_mode(dct);
  if (_f4u$t.is_panoramic(dct)) {
    options.a0 = 0;
    options.sweep = 360;
  }
  var size = _f4u$t.get_size(dct);
  options.ir *= size;

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.init = numspecs["init"];
  vbox_options.id = id;
  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.Y_AXIS;
  lm_options.stretchable = [false, false];

  /* make faust ui objects */
  var rbutton = new _f4u$t.RotatingButton(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = new _f4u$t.LayoutManager(lm_options);
  lm.objs.push(label);
  lm.objs.push(rbutton);
  lm.objs.push(vbox);

  return lm;
}

_f4u$t.make_hslider = function(dct, hash) {
  return _f4u$t.make_slider(_f4u$t.HorizontalSlider, dct, hash);
}

_f4u$t.make_vslider = function(dct, hash) {
  return _f4u$t.make_slider(_f4u$t.VerticalSlider, dct, hash);
}

_f4u$t.make_slider = function(kls, dct, hash) {
  if (_f4u$t.has_knob(dct)) {
    return _f4u$t.make_rbutton(dct, hash);
  }
  var numspecs = _f4u$t.getnumspecs(dct);
  var horizontal = kls == _f4u$t.HorizontalSlider;
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t[horizontal ? 'hslider_inits' : 'vslider_inits']);
  options.id = id;
  options.min = numspecs["min"];
  options.max = numspecs["max"];
  options.step = numspecs["step"];
  options.init = numspecs["init"];
  options.integer = numspecs["integer"];
  options.ndec = numspecs["ndec"];
  options.address = hash+dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  options.orientation = _f4u$t.get_orientation(dct);
  options.orientation_mode = _f4u$t.get_orientation_mode(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  var size = _f4u$t.get_size(dct);
  options.girth *= size;
  options.length *= size;

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.init = numspecs["init"];
  vbox_options.id = id;

  /* make faust ui objects */
  var slider = new kls(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = 0;
  if (horizontal) {
    var internal_lm_options = $.extend(true, {}, _f4u$t.hgroup_inits);
    internal_lm_options.axis = _f4u$t.X_AXIS
    internal_lm_options.draw_background = false;
    internal_lm_options.other_axis_padding = 0;
    var internal_lm = new _f4u$t.LayoutManager(internal_lm_options);
    internal_lm.objs.push(vbox);
    internal_lm.objs.push(slider);

    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.gravity = _f4u$t.LEFT;
    lm_options.stretchable = [true, false];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(internal_lm);
  } else {
    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.stretchable = [false, true];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(slider);
    lm.objs.push(vbox);
  }

  return lm;
}

_f4u$t.make_hbargraph = function(dct, hash) {
  return _f4u$t.make_bargraph(_f4u$t.HorizontalBarGraph, dct, hash);
}

_f4u$t.make_vbargraph = function(dct, hash) {
  return _f4u$t.make_bargraph(_f4u$t.VerticalBarGraph, dct, hash);
}

_f4u$t.make_bargraph = function(kls, dct, hash) {
  var horizontal = kls == _f4u$t.HorizontalBarGraph;
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t[horizontal ? 'hbargraph_inits' : 'vbargraph_inits']);
  options.id = id;
  //var numspecs = _f4u$t.getnumspecs(dct);
  options.min = parseFloat(dct["min"]);
  options.max = parseFloat(dct["max"]);
  options.address = hash+dct["address"];
  options.unit = _f4u$t.get_unit(dct);
  var size = _f4u$t.get_size(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  options.girth *= size;
  options.length *= size;

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.keysink = false;
  vbox_options.id = id;
  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.Y_AXIS;

  /* make faust ui objects */
  var bargraph = new kls(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = 0;
  // ugh...code dup from slider...
  if (horizontal) {
    var internal_lm_options = $.extend(true, {}, _f4u$t.hgroup_inits);
    internal_lm_options.axis = _f4u$t.X_AXIS
    internal_lm_options.draw_background = false;
    internal_lm_options.other_axis_padding = 0;
    var internal_lm = new _f4u$t.LayoutManager(internal_lm_options);
    internal_lm.objs.push(vbox);
    internal_lm.objs.push(bargraph);

    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.gravity = _f4u$t.LEFT;
    lm_options.stretchable = [true, false];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(internal_lm);
  } else {
    var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
    lm_options.axis = _f4u$t.Y_AXIS;
    lm_options.stretchable = [false, true];
    lm = new _f4u$t.LayoutManager(lm_options);
    lm.objs.push(label);
    lm.objs.push(bargraph);
    lm.objs.push(vbox);
  }

  return lm;
}

_f4u$t.make_button = function(dct, hash) {
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t.button_inits);
  options.id = id;
  options.label = dct.label;
  options.address = hash+dct.address;
  options.tooltip = _f4u$t.get_tooltip(dct);
  return new _f4u$t.Button(options);
}

_f4u$t.make_checkbox = function(dct, hash) {
  var id = _f4u$t.randString();
  var options = $.extend(true, {}, _f4u$t.checkbox_inits);
  options.id = id;
  options.address = hash+dct.address;
  options.init = (dct.init == "1" ? true : false);
  var size = _f4u$t.get_size(dct);
  options.tooltip = _f4u$t.get_tooltip(dct);
  options.d *= size;

  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.X_AXIS;
  lm_options.stretchable = [false, false];

  /* make faust ui objects */
  var checkbox = new _f4u$t.CheckBox(options);
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});

  var lm = new _f4u$t.LayoutManager(lm_options);
  lm.objs.push(checkbox);
  lm.objs.push(label);

  return lm;
}

_f4u$t.make_nentry = function(dct, hash) {
  if (_f4u$t.has_knob(dct)) {
    return _f4u$t.make_rbutton(dct, hash);
  }
  var numspecs = _f4u$t.getnumspecs(dct);
  var id = _f4u$t.randString();
  var options = {
    label : dct["label"],
    min : numspecs["min"],
    max : numspecs["max"],
    step : numspecs["step"],
    init : numspecs["init"],
    integer : numspecs["integer"],
    ndec : numspecs["ndec"],
    address : hash+dct["address"],
    unit : _f4u$t.get_unit(dct),
    tooltip : _f4u$t.get_tooltip(dct)
  };
  options.id = id;

  var nentry = new _f4u$t.NumericalEntry(options);

  var vbox_options = $.extend(true, {}, _f4u$t.vbox_inits);
  vbox_options.init = numspecs["init"];
  vbox_options.id = id;
  var lm_options = $.extend(true, {}, _f4u$t.vgroup_inits);
  lm_options.axis = _f4u$t.Y_AXIS;
  lm_options.stretchable = [false, false];

  /* make faust ui objects */
  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});
  var vbox = new _f4u$t.ValueBox(vbox_options);

  var lm = new _f4u$t.LayoutManager(lm_options);
  lm.objs.push(label);
  lm.objs.push(nentry);
  lm.objs.push(vbox);

  return lm;
}

_f4u$t.make_hgroup = function(dct, hash) {
  return _f4u$t.make_group(_f4u$t.X_AXIS, dct, hash);
}

_f4u$t.make_vgroup = function(dct, hash) {
  return _f4u$t.make_group(_f4u$t.Y_AXIS, dct, hash);
}

_f4u$t.make_group = function(axis, dct, hash) {
  var internal_options = $.extend(true, {}, _f4u$t.xy(axis, _f4u$t.hgroup_inits, _f4u$t.vgroup_inits));
  internal_options.axis = axis;

  internal_options.draw_background = false;
  internal_options.other_axis_padding = 0;
  var id = _f4u$t.randString();
  internal_options.id = id;

  var internal_lm = new _f4u$t.LayoutManager(internal_options);

  for (var i = 0; i < dct["items"].length; i++) {
    if (dct["items"][i]["type"] == "hgroup") {
      internal_lm.objs.push(_f4u$t.make_hgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vgroup") {
      internal_lm.objs.push(_f4u$t.make_vgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "tgroup") {
      internal_lm.objs.push(_f4u$t.make_tgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "hslider") {
      internal_lm.objs.push(_f4u$t.make_hslider(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vslider") {
      internal_lm.objs.push(_f4u$t.make_vslider(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "hbargraph") {
      internal_lm.objs.push(_f4u$t.make_hbargraph(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vbargraph") {
      internal_lm.objs.push(_f4u$t.make_vbargraph(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "button") {
      internal_lm.objs.push(_f4u$t.make_button(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "checkbox") {
      internal_lm.objs.push(_f4u$t.make_checkbox(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "nentry") {
      internal_lm.objs.push(_f4u$t.make_nentry(dct["items"][i], hash));
    }
    else {
      console.log("UFO: Unidentified Faust Object");
    }
  }

  var label = new _f4u$t.Label({label : _f4u$t.check_label(dct["label"]), id : id+"_label", mom : null});

  var options = $.extend(true, {}, _f4u$t.vgroup_inits);
  // needed for tab group
  options.label = dct["label"];
  options.axis = _f4u$t.Y_AXIS;

  var lm = new _f4u$t.LayoutManager(options);
  lm.objs.push(label);
  lm.objs.push(internal_lm);
  return lm;
}

_f4u$t.make_tgroup = function(dct, hash) {
  var options = $.extend(true, {}, _f4u$t.tgroup_inits);
  var tg = new _f4u$t.TabGroup(options);

  for (var i = 0; i < dct["items"].length; i++) {
    if (dct["items"][i]["type"] == "hgroup") {
      tg.objs.push(_f4u$t.make_hgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "vgroup") {
      tg.objs.push(_f4u$t.make_vgroup(dct["items"][i], hash));
    }
    else if (dct["items"][i]["type"] == "tgroup") {
      tg.objs.push(_f4u$t.make_tgroup(dct["items"][i], hash));
    }
    else {
      console.log("UFO: Unidentified Faust Object");
    }
  }

  return tg;
}

_f4u$t.json_to_ui = function(json, hash) {
  if (json["ui"][0]["type"] == "vgroup") {
    return _f4u$t.make_vgroup(json["ui"][0], hash);
  }
  else if (json["ui"][0]["type"] == "hgroup") {
    return _f4u$t.make_hgroup(json["ui"][0], hash);
  }
  else if (json["ui"][0]["type"] == "tgroup") {
    return _f4u$t.make_tgroup(json["ui"][0], hash);
  }
  else {
    console.log("UFO: Unidentified Faust Object");
  }
}
 
/*
 * look for the phrase
 * UI2DSP to see where the UI sends messages to DSP
 * obviously, the goal is to separate the two as much as possible
 */


/*
  UTILITY FUNCTIONS
*/
_f4u$t.getOperativeX = function(e) {
  return (e.clientX + $(document).scrollLeft()) / _f4u$t.VIEWPORT_SCALE;
}

_f4u$t.getOperativeY = function(e) {
  return (e.clientY + $(document).scrollTop()) / _f4u$t.VIEWPORT_SCALE;
}

_f4u$t.move_to_ridiculous_negative = function(id) {
  _f4u$t.generic_translate(id, -100000, -100000);
}

_f4u$t.devnull = function devnull() { }

_f4u$t.generic_translate = function(id, x, y) {
  var elt = document.getElementById(id);
  var transform = _f4u$t.transform_to_array(elt.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  transform[0][1] = x;
  transform[0][2] = y;
  var movetothis = _f4u$t.array_to_transform(transform);
  elt.setAttribute("transform", movetothis);
}

// parser of an object's transform

_f4u$t.transform_to_array = function(transform) {
  var out = [];
  var flre = "[-+]?[0-9]*\\.?[0-9]*(?:[eE][-+]?[0-9]+)?";
  var matrix = new RegExp("^\\s*matrix\\s*\\(\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*\\)");
  var translate = new RegExp("^\\s*translate\\s*\\(\\s*("+flre+")\\s*(?:[,]\\s*("+flre+")\\s*)?\\)");
  var scale = new RegExp("^\\s*scale\\s*\\(\\s*("+flre+")\\s*(?:[,]\\s*("+flre+")\\s*)?\\)");
  var rotate = new RegExp("^\\s*rotate\\s*\\(\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*[,]\\s*("+flre+")\\s*\\)");
  var skewX = new RegExp("^\\s*skewX\\s*\\(\\s*("+flre+")\\s*\\)");
  var skewY = new RegExp("^\\s*skewY\\s*\\(\\s*("+flre+")\\s*\\)");
  while(true) {
    var match = matrix.exec(transform);
    if (match != null) {
      out.push(["matrix",parseFloat(match[1]), parseFloat(match[2]), parseFloat(match[3]), parseFloat(match[4]), parseFloat(match[5]), parseFloat(match[6])]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = translate.exec(transform);
    if (match != null) {
      var second = 0.0;
      if (match[2] != undefined) { second = parseFloat(match[2]); }
      out.push(["translate",parseFloat(match[1]),second]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = scale.exec(transform);
    if (match != null) {
      var second = 0.0;
      if (match[2] != undefined) { second = parseFloat(match[2]); }
      out.push(["scale",parseFloat(match[1]), second]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = rotate.exec(transform);
    if (match != null) {
      var second = 0.0;
      if (match[2] != undefined) { second = parseFloat(match[2]); }
      var third = 0.0;
      if (match[2] != undefined) { third = parseFloat(match[2]); }
      out.push(["rotate",parseFloat(match[1]), second, third]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = skewX.exec(transform);
    if (match != null) {
      out.push(["skewX", parseFloat(match[1])]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    match = skewY.exec(transform);
    if (match != null) {
      out.push(["skewY", parseFloat(match[1])]);
      transform = transform.substr(match[0].length,transform.length-match[0].length);
      continue;
    }
    break;
  }
  return out;
}

// takes an array, turns it to a transform

_f4u$t.array_to_transform = function(array) {
  var out = "";
  while (array.length > 0)
  {
    out = out.concat(array[0][0]);
    out = out.concat("(");
    var i=1;
    var arlen = array[0].length;
    while(arlen > i) {
      out = out.concat(array[0][i]+",");
      i++;
    }
    out = out.substr(0,out.length-1);
    out = out.concat(") ");
    array.shift();
  }
  if (out.length > 0) { out = out.substr(0,out.length-1); }
  return out;
}

/*
  INITIALIZATION FUNCTIONS
*/

_f4u$t.initiate_nentry = function(fullid, minval, maxval, step, init, integer, ndec, label, unit, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "nentry";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"] = integer;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"] = ndec;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_slider = function(axis, fullid, length, sliderlen, minval, maxval, step, init, integer, ndec, label, unit, orientation, orientation_mode, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = (axis == _f4u$t.X_AXIS ? "hslider" : "vslider");
  _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"] = axis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["length"] = length;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["sliderlen"] = sliderlen;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["orientation"] = orientation;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["previousorientation"] = null;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["orientationmode"] = orientation_mode;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"] = integer;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"] = ndec;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_hslider = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, orientation_mode, address) {
  _f4u$t.initiate_slider(_f4u$t.X_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, orientation_mode, address);
}

_f4u$t.initiate_vslider = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, orientation_mode, address) {
  _f4u$t.initiate_slider(_f4u$t.Y_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, integer, ndec, label, unit, orientation, orientation_mode, address);
}

_f4u$t.initiate_bargraph = function(axis, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = (axis == _f4u$t.X_AXIS ? "hbargraph" : "vbargraph");
  _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"] = axis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["weakaxis"] = weakaxis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["strongaxis"] = strongaxis;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_hbargraph = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address) {
  _f4u$t.initiate_bargraph(_f4u$t.X_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address);
}

_f4u$t.initiate_vbargraph = function(fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address) {
  _f4u$t.initiate_bargraph(_f4u$t.Y_AXIS, fullid, weakaxis, strongaxis, minval, maxval, step, init, label, unit, address);
}

_f4u$t.initiate_rbutton = function(fullid,initangle,sweepangle,radius,knobpercentage,minval,maxval,step,init,integer,ndec,label,unit,orientation,orientation_mode,address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "rbutton";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"] = initangle;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"] = sweepangle;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["radius"] = radius;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["knobpercentage"] = knobpercentage;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["label"] = label;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"] = minval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"] = maxval;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["step"] = step;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = init;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"] = unit;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["orientation"] = orientation;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["previousorientation"] = null;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["orientationmode"] = orientation_mode;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"] = integer;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"] = ndec;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_checkbox = function(fullid, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "checkbox";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["time"] = 0;new Date().getTime();
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_button = function(fullid, upfill, downfill, address) {
  var id = _f4u$t.unique(fullid);
  _f4u$t.IDS_TO_ATTRIBUTES[id] = {};
  _f4u$t.IDS_TO_ATTRIBUTES[id]["type"] = "button";
  _f4u$t.IDS_TO_ATTRIBUTES[id]["upfill"] = upfill;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["downfill"] = downfill;
  _f4u$t.IDS_TO_ATTRIBUTES[id]["address"] = address;
  _f4u$t.path_to_id(address, fullid);
}

_f4u$t.initiate_tab_group = function(index, ids) {
  var strar = ids.toString().split('#');
  // boo svg...tags
  for (var i = 0; strar.length > i; i++) {
    if (i != index) {
      _f4u$t.move_to_ridiculous_negative(strar[i]);
    }
  }
}

/*
  ACTIVATION FUNCTIONS
  Activates UI objects as being in focus
*/

_f4u$t.nentry_down_minus = function(ee) {
  _f4u$t.activate_nentry(ee, -1);
}

_f4u$t.nentry_down_plus = function(ee) {
  _f4u$t.activate_nentry(ee, 1);
}

_f4u$t.nentry_up_minus = function(ee) {
  _f4u$t.disactivate_nentry(ee, -1);
}

_f4u$t.nentry_up_plus = function(ee) {
  _f4u$t.disactivate_nentry(ee, 1);
}

_f4u$t.disactivate_nentry = function(ee, dir) {
  // it is possible that an object is touched by multiple fingers at the
  // same time
  // if the id is already being used, we ignore
  // otherwise, use the first in the array...
  var identifier = ee.originalEvent.changedTouches ? ee.originalEvent.changedTouches[0].identifier : 0;
  var longid = ee.target.id;
  var id = _f4u$t.unique(longid);
  _f4u$t.nentry_fill_changer(id, false, dir);
}

_f4u$t.activate_nentry = function(ee, dir) {
  // it is possible that an object is touched by multiple fingers at the
  // same time
  // if the id is already being used, we ignore
  // otherwise, use the first in the array...
  var identifier = ee.originalEvent.changedTouches ? ee.originalEvent.changedTouches[0].identifier : 0;
  var longid = ee.target.id;
  var id = _f4u$t.unique(longid);
  _f4u$t.nentry_fill_changer(id, true, dir);
  _f4u$t._I[identifier] = {id : longid, moved : false, value : null, address : _f4u$t.IDS_TO_ATTRIBUTES[id]["address"]};
  _f4u$t.active_addresses.push(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"]);

  var now = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]);
  if (dir == 1) {
    now += _f4u$t.IDS_TO_ATTRIBUTES[id]["step"];
  }
  else {
    now -= _f4u$t.IDS_TO_ATTRIBUTES[id]["step"];
  }

  now = _f4u$t.quantize(now, _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["step"]);
  now = _f4u$t.dumb_label_update(_f4u$t.unique(_f4u$t._I[identifier].id), now);
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], now);
  return now;
}

_f4u$t.activate_hslider = function(ee) {
  _f4u$t.activate_slider(ee);
}

_f4u$t.activate_vslider = function(ee) {
  _f4u$t.activate_slider(ee);
}

_f4u$t.activate_slider = function(ee) {
  _f4u$t.activate_moving_object(ee);
}

_f4u$t.activate_rbutton = function(ee) {
  _f4u$t.activate_moving_object(ee);
}

_f4u$t.activate_moving_object = function(ee) {
  var touches = ee.changedTouches || [ee];
  if (ee.originalEvent) {
    touches = ee.originalEvent.changedTouches || [ee];
  }
  var identifier = touches[0].identifier || 0;
  var longid = touches[0].target.id;
  var id = _f4u$t.unique(longid);
  _f4u$t._I[identifier] = {id : longid, moved : false, value : null, address : _f4u$t.IDS_TO_ATTRIBUTES[id]["address"]};
  _f4u$t.active_addresses.push(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"]);
  // turns off zoom for mobile devices
  $('body').bind('touchmove', function(event) { event.preventDefault() });
  // if we touch a groove, we want the object to snap to the correct position, so
  // we need to call the move function.
  _f4u$t.move_active_object(ee);
}

_f4u$t.activate_tgroup = function(x, y, goodid, badids) {
  var strar = badids.toString().split('#');
  for (var i = 0; strar.length > i; i++) {
    _f4u$t.move_to_ridiculous_negative(strar[i]);
    _f4u$t.tgroup_fill_changer(_f4u$t.unique(strar[i]), false);
  }
  _f4u$t.generic_translate(goodid, x, y);
  _f4u$t.tgroup_fill_changer(_f4u$t.unique(goodid), true);
}

/*
  MOVING FUNCTIONS.
  Functions that take care of moving the active object on the screen.
*/

_f4u$t.tooltip_mouseover = function(e) {
  var id = _f4u$t.unique(e.target.id);
  var full_id = 'faust_tooltip_'+id;
  document.getElementById(full_id).setAttribute("style","opacity:1.0");
  setTimeout(function () {
    _f4u$t.generic_translate(full_id, 0, 0);
    var os = $(document.getElementById(full_id)).offset();
    var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;
    var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
    _f4u$t.generic_translate(full_id, _f4u$t.getOperativeX(e) - my_x, _f4u$t.getOperativeY(e) - my_y);
  }, 500);
}

_f4u$t.tooltip_mouseout = function(e) {
  var id = _f4u$t.unique(e.target.id);
  var full_id = 'faust_tooltip_'+id
  _f4u$t.move_to_ridiculous_negative(full_id);
  document.getElementById(full_id).setAttribute("style","opacity:0.0");
}

// main function to move currently-selected slider
_f4u$t.move_active_object = function(ee) {
  for (var elt in _f4u$t._I) {
    if (_f4u$t._I[elt] && (elt.indexOf('orientation') == -1)) {
      var touches = ee.touches || [ee];
      if (ee.originalEvent) {
        touches = ee.originalEvent.touches || [ee];
      }
      for (var i = 0; i < touches.length; i++) {
        _f4u$t.internal_move_active_object(touches[i], touches[0] == ee ? 0 : touches[i].identifier);
      }
      // breaks loop, as we just need one active element for this to work
      return true;
    }
  }
  return true;
}

// TODO
// Does this really need to be a separate function.
// Helps for readability, but not necessary
_f4u$t.internal_move_active_object = function(e, identifier) {
  _f4u$t.clog_key_sink();
  var fn = _f4u$t['move_active_'+_f4u$t.type(_f4u$t._I[identifier]['id'])];
  var now = null;
  if (fn) {
   now =  fn(e, identifier);
  }

  // UI2DSP
  if (now != null && now != _f4u$t._I[identifier]['value']) {
    var id = _f4u$t.unique(_f4u$t._I[identifier]['id']);
    _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], now);
    _f4u$t._I[identifier]['value'] = now;
  }

  return now;
}

_f4u$t.redraw_slider_groove = function(id, axis, length, perc) {
  perc = _f4u$t.bound(perc, 0, 1); // to avoid mouse spillover on either side of slider
  var groove = document.getElementById('faust_'+(_f4u$t.xy(axis,'hslider','vslider'))+'_groove_'+id);
  if (axis == _f4u$t.X_AXIS) {
    groove.setAttribute('x', length * perc)
    groove.setAttribute('width', length * (1 - perc));
  }
  if (axis == _f4u$t.Y_AXIS) {
    groove.setAttribute('height', length * perc);
  }
}

_f4u$t.move_active_slider = function(e,identifier)
{
  var id = _f4u$t.unique(_f4u$t._I[identifier].id);
  var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
  var sliding_part = document.getElementById(_f4u$t.xy(axis, 'faust_hslider_handle_', 'faust_vslider_handle_')+id);
  var anchor = document.getElementById(_f4u$t.xy(axis, 'faust_hslider_meter_', 'faust_vslider_meter_')+id);
  var sliderlen = _f4u$t.IDS_TO_ATTRIBUTES[id]["sliderlen"];
  var length = _f4u$t.IDS_TO_ATTRIBUTES[id]["length"];
  var pos = -1;
  var os = $(anchor).offset();
  var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;
  var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
  // we only care about the axis of the slider
  if (axis == _f4u$t.X_AXIS) {
    pos = _f4u$t.getOperativeX(e) - my_x;
  }
  else {
    pos = _f4u$t.getOperativeY(e) - my_y;
  }

  pos -= (sliderlen / 2.0);
  var transform = _f4u$t.transform_to_array(sliding_part.getAttribute("transform"));
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = pos;//transform[0][axis + 1] + diff;
  // minimum of the slider is to the bottom / left
  transform[0][axis + 1] = _f4u$t.bound_and_avoid_large_leaps(aval, transform[0][axis + 1], 0, length - sliderlen);
  _f4u$t.redraw_slider_groove(
    id,
    axis,
    length,
    aval / length
  );
  var now = _f4u$t[_f4u$t.xy(axis, "generic_label_update", "generic_flipped_label_update")](id, aval, 0, length - sliderlen);
  var movetothis = _f4u$t.array_to_transform(transform);
  sliding_part.setAttribute("transform", movetothis);
  return now;
}

_f4u$t.move_active_vslider = _f4u$t.move_active_slider;
_f4u$t.move_active_hslider = _f4u$t.move_active_slider;

_f4u$t.touched = function(id) {
  for (var identifier in _f4u$t._I) {
    if ((identifier != ('orientation'+id))
        && (_f4u$t._I[identifier].id.indexOf(id) != -1)) {
      return true;
    }
  } 
  return false;
}

_f4u$t.respondToOrientationChange = function(e) {
  for (var id in _f4u$t.IDS_TO_ATTRIBUTES) {
    if (_f4u$t.IDS_TO_ATTRIBUTES[id].orientation &&
        _f4u$t.IDS_TO_ATTRIBUTES[id].orientation.angle)
      {
        if (!_f4u$t._I['orientation'+id]) {
          _f4u$t._I['orientation'+id] = {id : id, moved : false, value : null, address : _f4u$t.IDS_TO_ATTRIBUTES[id]["address"]};
        }
        var now = null;
        if (((_f4u$t.IDS_TO_ATTRIBUTES[id]["type"] == 'hslider')
             || (_f4u$t.IDS_TO_ATTRIBUTES[id]["type"] == 'vslider'))
            && !_f4u$t.touched(id)) {
           // ugh...this means that they will not be disactivated...
           _f4u$t.active_addresses.push(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"]);
          now = _f4u$t.moveSliderViaAccelerometer(e, id);
        }
        // UI2DSP
        if (now != null && now != _f4u$t._I['orientation'+id]['value']) {
          _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], now);
          _f4u$t._I['orientation'+id]['value'] = now;
        }
      }
  }
}

// TODO...combine this with above...
// simplified version, so shouldn't be too hard
_f4u$t.moveSliderViaAccelerometer = function(e, longid) {
  var id = _f4u$t.unique(longid);
  var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
  var sliding_part = document.getElementById(_f4u$t.xy(axis, 'faust_hslider_handle_', 'faust_vslider_handle_')+id);
  var sliderlen = _f4u$t.IDS_TO_ATTRIBUTES[id]["sliderlen"];
  var length = _f4u$t.IDS_TO_ATTRIBUTES[id]["length"];
  var orientation = e[_f4u$t.IDS_TO_ATTRIBUTES[id].orientation.angle]
                    ? e[_f4u$t.IDS_TO_ATTRIBUTES[id].orientation.angle]
                    : 0;
  var prev_orientation = _f4u$t.IDS_TO_ATTRIBUTES[id].previousorientation != null
                         ? _f4u$t.IDS_TO_ATTRIBUTES[id].previousorientation
                         : e[_f4u$t.IDS_TO_ATTRIBUTES[id].orientation.angle];
  var transform = _f4u$t.transform_to_array(sliding_part.getAttribute("transform"));
  _f4u$t.IDS_TO_ATTRIBUTES[id].previousorientation = e[_f4u$t.IDS_TO_ATTRIBUTES[id].orientation.angle];
  var aval = 0;
  if (_f4u$t.IDS_TO_ATTRIBUTES[id].orientationmode == 'relative') {
    var nudge = (orientation - prev_orientation) * (length - sliderlen) / (_f4u$t.IDS_TO_ATTRIBUTES[id].orientation.high - _f4u$t.IDS_TO_ATTRIBUTES[id].orientation.low);
    aval = transform[0][axis + 1] + nudge;
    
  } else {
    aval = _f4u$t.remap(orientation,
                        _f4u$t.IDS_TO_ATTRIBUTES[id].orientation.low,
                        _f4u$t.IDS_TO_ATTRIBUTES[id].orientation.high,
                        0,
                        length - sliderlen);
  }
  // minimum of the slider is to the bottom / left
  transform[0][axis + 1] = _f4u$t.bound_and_avoid_large_leaps(aval, transform[0][axis + 1], 0, length - sliderlen);
  _f4u$t.redraw_slider_groove(
    id,
    axis,
    length,
    aval / length
  );
  var now = _f4u$t[_f4u$t.xy(axis, "generic_label_update", "generic_flipped_label_update")](id, aval, 0, length - sliderlen);
  var movetothis = _f4u$t.array_to_transform(transform);
  sliding_part.setAttribute("transform", movetothis);
  return now;
}

_f4u$t.redrawRotatingButtonMeter = function(id, initangle, sweepangle, radius, knobpercentage, startp) {
  var meter = document.getElementById('faust_rbutton_meter_'+id);
  var xo = radius;
  var yo = radius;

  var d = "M{0} {1}A{2} {3} 0 {4} {5} {6} {7}L{8} {9}A{10} {11} 0 {12} {13} {14} {15}L{16} {17}";
  d = d.format([
    radius * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    radius * Math.sin(_f4u$t.d2r(startp)) + yo, // outside Y
    radius, // radius X
    radius, // radius Y
    initangle + sweepangle - startp <= 180 ? 0 : 1, // large arc flag
    1, // draw positive
    radius * Math.cos(_f4u$t.d2r(initangle + sweepangle)) + xo, // endpoint X
    radius * Math.sin(_f4u$t.d2r(initangle + sweepangle)) + yo, // endpoint Y
    radius * knobpercentage * Math.cos(_f4u$t.d2r(initangle + sweepangle)) + xo, // inside endpoint X
    radius * knobpercentage * Math.sin(_f4u$t.d2r(initangle + sweepangle)) + yo, // inside endpoint Y
    radius * knobpercentage, // inside radiux X
    radius * knobpercentage, // inside radiux Y
    initangle + sweepangle - startp <= 180 ? 0 : 1, // large arc flag
    0, // draw negative
    radius * knobpercentage * Math.cos(_f4u$t.d2r(startp)) + xo, // inside X
    radius * knobpercentage * Math.sin(_f4u$t.d2r(startp)) + yo, // inside Y
    radius * Math.cos(_f4u$t.d2r(startp)) + xo, // outside X
    radius * Math.sin(_f4u$t.d2r(startp)) + yo// outside Y
  ]);

  meter.setAttribute("d", d);
}

_f4u$t.move_active_rbutton = function(e, identifier)
{
  var id = _f4u$t.unique(_f4u$t._I[identifier].id);
  var sliding_part = document.getElementById('faust_rbutton_handle_'+id);
  var anchor = document.getElementById('faust_rbutton_anchor_'+id);
  var initangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"];
  var sweepangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"];
  var os = $(anchor).offset();
  var my_x = os['left'] / _f4u$t.VIEWPORT_SCALE;
  var my_y = os['top'] / _f4u$t.VIEWPORT_SCALE;
  var transform = _f4u$t.transform_to_array(sliding_part.getAttribute("transform"));

  var diff = 180. * Math.atan2(_f4u$t.getOperativeY(e) - my_y, _f4u$t.getOperativeX(e) - my_x) / Math.PI;
  while (diff < 0) {
    diff += 360;
  }
  diff = diff % 360;
  // put it between the values if necessary
  if (((360 + diff) >= initangle) && ((360 + diff) <= (initangle + sweepangle))) {
    diff += 360;
  }

  if (e.target.id.indexOf('dot') != -1) {
    // if it is a panoramic dot, snap to the multiple of 45
    diff = parseInt((diff / 45) + 0.5) * 45;
  }
  // we assume that there is only one element and that it is a transform
  // make sure to change this if things get more complicated
  // actually, just make sure not to make things more complicated...

  var aval = diff;
  var rotation = transform[2][1];
  if ((aval >= initangle) && (aval <= (initangle + sweepangle))) {
    // only change rotation if we're in bounds and the difference is small (choose 10 as epsilon)
    rotation = _f4u$t.bound_and_avoid_large_leaps(aval, transform[2][1], initangle, initangle + sweepangle, 10);
  }
  transform[2][1] = rotation;
  if (sweepangle != 360) {
    _f4u$t.redrawRotatingButtonMeter(
      id,
      initangle,
      sweepangle,
      _f4u$t.IDS_TO_ATTRIBUTES[id]["radius"],
      _f4u$t.IDS_TO_ATTRIBUTES[id]["knobpercentage"],
      transform[2][1]
    );
  }
  var now = _f4u$t.generic_label_update(id, rotation, initangle, initangle + sweepangle);
  var movetothis = _f4u$t.array_to_transform(transform);
  sliding_part.setAttribute("transform", movetothis);
  return now;
}

// gets rid of the current thing being dragged
_f4u$t.clearIdCache = function(ee) {
  if (ee) {
    // sometimes, there will be no event passed in (i.e. a button)
    // if so, we can skip everything below
    var touches = ee.changedTouches || [ee];
    if (ee.originalEvent) {
      touches = ee.originalEvent.changedTouches || ee;
    }
    for (var i = 0; i < touches.length; i++) {
      if (_f4u$t._I[touches[i].identifier || 0]) {
        var addr = _f4u$t._I[touches[i].identifier || 0].address;
        while (_f4u$t.active_addresses.indexOf(addr) !== -1) {
          _f4u$t.active_addresses.splice(_f4u$t.active_addresses.indexOf(addr), 1);
        }
        delete _f4u$t._I[touches[i].identifier || 0];
      }
    }
    // exit function before unbinding if there are still active elements
    for (var elt in _f4u$t._I) {
      if (_f4u$t._I[elt]) {
        return true;
      }
    }
  }
  // clear gunk out of cache
  _f4u$t._I = {};
  _f4u$t.active_addresses = [];
  $('body').unbind('touchmove'); // turns on zooming for mobile devices
}

_f4u$t.onoff_property_changer = function(id, down, property, value_down, value_up) {
  if (down) {
    $('#'+id).css(property, value_down);
  }
  else {
    $('#'+id).css(property, value_up);
  }
}

_f4u$t.onoff_fill_changer = function(id, down, value_down, value_up) {
  _f4u$t.onoff_property_changer(id, down, 'fill', value_down, value_up);
}

_f4u$t.button_fill_changer = function(id, down) {
  _f4u$t.onoff_fill_changer('faust_button_box_'+_f4u$t.unique(id), down, 'url(#buttonDownGradient)', 'url(#buttonUpGradient)');
}

_f4u$t.tgroup_fill_changer = function(id, down) {
  _f4u$t.onoff_fill_changer('faust_tab_'+_f4u$t.unique(id), down, 'url(#tabGroupDownGradient)', 'url(#tabGroupUpGradient)');
}

_f4u$t.nentry_fill_changer = function(id, down, dir) {
  var dirtext = dir == -1 ? 'minus' : 'plus';
  _f4u$t.onoff_fill_changer('faust_nentry_button_'+dirtext+'_'+_f4u$t.unique(id), down, 'url(#numericalEntryDownGradient)', 'url(#numericalEntryUpGradient)');
}

/*
  Note that hovering does not make sense for mobile devices.
  Unfortunately, some mobile device translate hover instructions
  as a sort of onclick command.
  So we remove this for mobile devices after the callback fires.
*/

_f4u$t.button_hover = function(id) {
  if(! /Android|webOS|iPhone|iPad|iPod|BlackBerry/i.test(navigator.userAgent) ) {
    $('#faust_button_box_'+_f4u$t.unique(id)).css('stroke', 'orange');
    $('#faust_label_'+_f4u$t.unique(id)).css('fill', 'orange');
  }
}

_f4u$t.button_unhover = function(id) {
  if(! /Android|webOS|iPhone|iPad|iPod|BlackBerry/i.test(navigator.userAgent) ) {
    $('#faust_button_box_'+_f4u$t.unique(id)).css('stroke', 'black');
    $('#faust_label_'+_f4u$t.unique(id)).css('fill', 'black');
  }
}

_f4u$t.button_up = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.button_fill_changer(id, false);
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], 0);
  _f4u$t.clearIdCache();
}

_f4u$t.button_down = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.clog_key_sink();
  _f4u$t.button_fill_changer(id, true);
  _f4u$t.fausthandler(_f4u$t.IDS_TO_ATTRIBUTES[id]["address"], 1);
}

_f4u$t.click_checkbox = function(I) {
  _f4u$t.change_checkbox(I, false);
}
_f4u$t.touch_checkbox = function(I) {
  _f4u$t.change_checkbox(I, true);
}

_f4u$t.change_checkbox = function(I, touch) {
  var id = _f4u$t.unique(I)
  var now = new Date().getTime();
  if (touch && ((now - _f4u$t.IDS_TO_ATTRIBUTES[id]["time"]) < 1000)) {
    return;
  }
  _f4u$t.IDS_TO_ATTRIBUTES[id]["time"] = now;
  _f4u$t.clog_key_sink();
  var address = _f4u$t.IDS_TO_ATTRIBUTES[id]["address"];
  var box = document.getElementById('faust_checkbox_check_'+id);
  var opacity = 0;
  if (box.style.opacity == 1.0) {
    opacity = 0;
  }
  else if (box.style.opacity == 0.0) {
    opacity = 1;
  }
  else {
    alert("malfunctional checkbox");
  }
  box.style.opacity = opacity;
  // UI2DSP
  _f4u$t.fausthandler(address, opacity);
}

/*
  TEXT UPDATES
  Functions that take care of updating text based either on
  keyboard input or objects' moving.
*/

_f4u$t.generic_label_update = function(id, c, l, h) {
  var now = _f4u$t.remap_and_quantize(c, l, h, _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["step"]);
  return _f4u$t.dumb_label_update(id, now);
}

_f4u$t.generic_flipped_label_update = function(id, c, l, h) {
  var now = _f4u$t.remap_and_quantize_and_flip(c, l, h, _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"], _f4u$t.IDS_TO_ATTRIBUTES[id]["step"]);
  return _f4u$t.dumb_label_update(id, now);
}

_f4u$t.change_label_text = function(label, id)
{
  label.textContent = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] + _f4u$t.IDS_TO_ATTRIBUTES[id]["unit"];
}

_f4u$t.dumb_label_update = function(id, c) {
  var label = document.getElementById("faust_value_value_"+id);
  var integer = _f4u$t.IDS_TO_ATTRIBUTES[id]["integer"];
  if (integer) {
    c = (c + 0.49999).toString().parseInt();
  }
  else {
    c = c.toFixed(_f4u$t.IDS_TO_ATTRIBUTES[id]["ndec"]);
  }
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = c;
  _f4u$t.change_label_text(label, id);;
  return c;
}

_f4u$t.clog_key_sink = function() {
  if (_f4u$t._N != 0) {
    var box = document.getElementById("faust_value_box_"+_f4u$t.unique(_f4u$t._N));
    box.style.stroke = "black";
    _f4u$t.ajax_queue_busy = false;
  }
  _f4u$t._N = 0;
}

_f4u$t.actualize_buffer = function() {
  // get a valid number in there...
  var id = _f4u$t.unique(_f4u$t._N);

  var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
  var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
  var address = _f4u$t.IDS_TO_ATTRIBUTES[id]["address"];

  if (isNaN(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"])) {
    _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = ""+_f4u$t.IDS_TO_ATTRIBUTES[id]["init"];
  }
  var c = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]);
  var label = document.getElementById(_f4u$t._N);
  var now = _f4u$t.bound(c, minval, maxval);
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = ""+now;
  _f4u$t.change_label_text(label, id);
  _f4u$t.IDS_TO_ATTRIBUTES[id]["init"] = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]; // prevents bad snaps of values

  // UI2DSP
  _f4u$t.fausthandler(address, now);

  _f4u$t.actualize_incremental_object(id);
}

_f4u$t.buffer_backspace = function() {
  var id = _f4u$t.unique(_f4u$t._N);
  if (_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"].length == 0) {
    return 0;
  }
  _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] = _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"].substring(0, _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"].length - 1);
  var label = document.getElementById(_f4u$t._N);
  _f4u$t.change_label_text(label, id);;
}

_f4u$t.make_delete_key_work = function(e) {
  if (e.keyCode == 8) {
    _f4u$t.buffer_backspace();
  }
}

_f4u$t.keys_to_sink = function(e) {
  if (_f4u$t._N == "") {
    return 0;
  }
  var id = _f4u$t.unique(_f4u$t._N);
  if (e.keyCode == 13) {
    _f4u$t.actualize_buffer();
    _f4u$t.clog_key_sink();
    return;
  }
  else {
    var key = e.keyCode;
    var str = String.fromCharCode(key)
    _f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"] += str;
  }
  var label = document.getElementById(_f4u$t._N);
  _f4u$t.change_label_text(label, id);;
}

_f4u$t.make_key_sink = function(I) {
  if (_f4u$t.ajax_queue_busy) {
    return false;
  }
  _f4u$t._N = 'faust_value_value_'+I;
  _f4u$t.IDS_TO_ATTRIBUTES[I]["buffer"] = "";
  var box = document.getElementById("faust_value_box_"+I);
  box.style.stroke = "red";
  _f4u$t.ajax_queue_busy = true;
  // below is a hack for text inputs that should only be activated
  // after some work is done to figure out how to prevent auto zooming
  // in mobile devices
  //document.getElementById('faust-text-input-dummy').focus();
}

_f4u$t.generic_key_sink = function(I) {
  var id = _f4u$t.unique(I);
  _f4u$t.make_key_sink(id);
  _f4u$t._I = {};
  _f4u$t.active_addresses = [];
}

_f4u$t.hslider_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

_f4u$t.vslider_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

_f4u$t.rotating_button_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

_f4u$t.nentry_key_sink = function(I) {
  _f4u$t.generic_key_sink(I);
}

// if a numerical entry is linked to an incremental object,
// actualize it

_f4u$t.actualize_incremental_object = function(id) {
  var hslider_id = "faust_hslider_handle_"+id;
  var vslider_id = "faust_vslider_handle_"+id;
  var rotating_button_id = "faust_rbutton_handle_"+id;
  var hbargraph_id = "faust_hbargraph_curtain_"+id;
  var vbargraph_id = "faust_vbargraph_curtain_"+id;
  var val = parseFloat(_f4u$t.IDS_TO_ATTRIBUTES[id]["buffer"]);
  var maybe_slider = document.getElementById(hslider_id);
  if (maybe_slider == null) {
    maybe_slider = document.getElementById(vslider_id);
  }
  var maybe_button = document.getElementById(rotating_button_id);
  var maybe_bargraph = document.getElementById(hbargraph_id);
  if (maybe_bargraph == null) {
    maybe_bargraph = document.getElementById(vbargraph_id);
  }
  if (maybe_slider != null) {
    // ugh...code dups
    var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
    var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
    var length = _f4u$t.IDS_TO_ATTRIBUTES[id]["length"];
    var sliderlen = _f4u$t.IDS_TO_ATTRIBUTES[id]["sliderlen"];
    var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
    val = _f4u$t[_f4u$t.xy(axis, "remap", "remap_and_flip")](val, minval, maxval, 0, length - sliderlen);
    var transform = _f4u$t.transform_to_array(maybe_slider.getAttribute("transform"));
    transform[0][axis + 1] = val;
    _f4u$t.redraw_slider_groove(
      id,
      axis,
      length,
      val / length
    );
    var movetothis = _f4u$t.array_to_transform(transform);
    maybe_slider.setAttribute("transform", movetothis);
    return 0;
  }
  else if (maybe_button != null) {
    var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
    var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
    var initangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"];
    var sweepangle = _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"];
    val = _f4u$t.remap(val, minval, maxval, initangle, initangle + sweepangle);
    var transform = _f4u$t.transform_to_array(maybe_button.getAttribute("transform"));
    transform[2][1] = val;
    if (sweepangle != 360) {
      _f4u$t.redrawRotatingButtonMeter(
        id,
        _f4u$t.IDS_TO_ATTRIBUTES[id]["initangle"],
        _f4u$t.IDS_TO_ATTRIBUTES[id]["sweepangle"],
        _f4u$t.IDS_TO_ATTRIBUTES[id]["radius"],
        _f4u$t.IDS_TO_ATTRIBUTES[id]["knobpercentage"],
        transform[2][1]
      );
    }
    var movetothis = _f4u$t.array_to_transform(transform);
    maybe_button.setAttribute("transform", movetothis);
    return 0;
  }
  else if (maybe_bargraph != null) {
    // ugh...code dups
    var minval = _f4u$t.IDS_TO_ATTRIBUTES[id]["minval"];
    var maxval = _f4u$t.IDS_TO_ATTRIBUTES[id]["maxval"];
    var axis = _f4u$t.IDS_TO_ATTRIBUTES[id]["axis"];
    var weakaxis = _f4u$t.IDS_TO_ATTRIBUTES[id]["weakaxis"];
    var strongaxis = _f4u$t.IDS_TO_ATTRIBUTES[id]["strongaxis"];
    val = _f4u$t[_f4u$t.xy(axis, "remap_and_flip", "remap_and_flip")](val, minval, maxval, 0, strongaxis);
    val = _f4u$t.bound(val, 0, strongaxis);
    /*
    // for paths...
    var newd = _f4u$t.xy(
      axis,
      'M 0 0L'+val+' 0L'+val+' '+weakaxis+'L0 '+weakaxis+'L0 0',
      'M 0 '+strongaxis+'L'+weakaxis+' '+strongaxis+'L'+weakaxis+' '+val+'L0 '+val+'L0 '+strongaxis
    );
    maybe_bargraph.setAttribute("d", newd);
    */
    maybe_bargraph.setAttribute("width", Math.max(0,_f4u$t.xy(axis, val, weakaxis)));
    maybe_bargraph.setAttribute("height", Math.max(0, _f4u$t.xy(axis, weakaxis, val)));
    return 0;
  }
  // no corresponding incremental object
  return 0;
}


/*
 DOCUMENT-WIDE DECLARATIONS
*/
_f4u$t.alert = function () { alert("moved"); }
document.onkeypress = _f4u$t.keys_to_sink;
document.onkeydown = _f4u$t.make_delete_key_work;
document.onmouseup = _f4u$t.clearIdCache;
document.onmousemove = _f4u$t.move_active_object;
document.ontouchend = _f4u$t.clearIdCache;
document.ontouchmove = _f4u$t.move_active_object;
window.ondeviceorientation = _f4u$t.respondToOrientationChange;
// make the entire document clickable for mobile devices
document.onclick = _f4u$t.devnull; 
/**
 Each audio bridge reports a callback that the listener calls with an address of
 a UI object and the value it is changing to.  The bridge is resonsible for
 using this information in a useful way (sending it to a server, to a
 JavaScript object, etc.).

@property HANDLER_CALLBACKS
@for _f4u$t
@type Array
@default []
**/
_f4u$t.HANDLER_CALLBACKS = [];

/**
 Triggers all callbacks.

@method fausthandler
@for _f4u$t
@static
@param {String} dest The destination address
@param {Number} value The value at that address.
**/

_f4u$t.fausthandler = function(dest, value) {
  for (var i = 0; i < _f4u$t.HANDLER_CALLBACKS.length; i++) {
    _f4u$t.HANDLER_CALLBACKS[i](dest, value);
  }
}

// Functions to update UI via what's happening internally in the audio
// processing.

_f4u$t.update_incremental_object_value = function(address, value) {
   var id = _f4u$t.PATHS_TO_IDS[address];
  _f4u$t.dumb_label_update(_f4u$t.unique(id), value);
  _f4u$t.actualize_incremental_object(_f4u$t.unique(id));
}

_f4u$t.update_hslider_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_vslider_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_hbargraph_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_vbargraph_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_rbutton_value = function(address, value) {
  _f4u$t.update_incremental_object_value(address, value);
}

_f4u$t.update_nentry_value = function(address, value) {
   var id = _f4u$t.PATHS_TO_IDS[address];
  _f4u$t.dumb_label_update(id, value);
}

_f4u$t.update_checkbox_value = function(address, value) {
  // perhaps too much UI here?
  var id = _f4u$t.PATHS_TO_IDS[address];
  // for latency issues...seems not to do anything, so commented out
  /*if (now - _f4u$t.IDS_TO_ATTRIBUTES[id]["time"] < 2000) {
    return;
  }*/
  var check = document.getElementById('faust_checkbox_check_'+id);
  check.style.opacity = value;
}

_f4u$t.update_button_value = function(address, value) {
  var id = _f4u$t.PATHS_TO_IDS[address];
  if (value == 1) {
    _f4u$t.button_fill_changer(id, true);
  } else {
    _f4u$t.button_fill_changer(id, false);
  }
}

_f4u$t.update_value_at_address = function(address, value) {
  var id = _f4u$t.PATHS_TO_IDS[address];
  var kind = _f4u$t.IDS_TO_ATTRIBUTES[id] ? _f4u$t.IDS_TO_ATTRIBUTES[id].type : null ;
  if (kind == 'vslider') { _f4u$t.update_vslider_value(address, value); }
  else if (kind == 'hslider') { _f4u$t.update_hslider_value(address, value); }
  else if (kind == 'rbutton') { _f4u$t.update_rbutton_value(address, value); }
  else if (kind == 'checkbox') { _f4u$t.update_checkbox_value(address, value); }
  else if (kind == 'button') { _f4u$t.update_button_value(address, value); }
  else if (kind == 'nentry') { _f4u$t.update_nentry_value(address, value); }
  else if (kind == 'vbargraph') { _f4u$t.update_vbargraph_value(address, value); }
  else if (kind == 'hbargraph') { _f4u$t.update_hbargraph_value(address, value); }
  else { if (0) { console.log("Unidentified Faust Object (UFO) "+id+" "+kind); }}
}
 

//-----------------------------------------------------------------------------
// handlers to send a faust 'set' message
// actually using a 'GET' method
//-----------------------------------------------------------------------------
_f4u$t.faust_server_handler = function(dest, value) {
  if (!_f4u$t.ajax_queue[dest]) {
    _f4u$t.ajax_queue[dest] = [];
  }
  _f4u$t.ajax_queue[dest].push({request : dest +"?value=" + value, time : new Date().getTime()});
}

_f4u$t.server_update_function = function(address, value) {
  // do nothing - a stub that should be overwritten in toplevel html files
}

//-----------------------------------------------------------------------------
// poll current values from the server
//-----------------------------------------------------------------------------

_f4u$t.dispatch = function(data) {
  var lines = data.toString().split('\n');
  var limit = lines.length;
  for (i=0; i < limit; i++) {
    var values = lines[i].toString().split(' ');
    if (values.length > 1) {
      var address = values[0];
      // skip things being moved to avoid interference
      if (_f4u$t.active_addresses.indexOf(address) != -1) {
        continue;
      }
      var value = Math.round(values[1]*10000)/10000;
      _f4u$t.server_update_function(address, value);
    }
  }
}

_f4u$t.ajax_queue_length = function() {
  var l = 0;
  for (var key in _f4u$t.ajax_queue) {
    for (var i = 0; i < _f4u$t.ajax_queue[key].length; i++) {
      l += 1;
    }
  }
  return l;
}

_f4u$t.ajax_queue_get_request_and_trim = function () {
  var t = Number.POSITIVE_INFINITY;
  var request = '';
  var mykey = '';
  for (var key in _f4u$t.ajax_queue) {
    for (var i = 0; i < _f4u$t.ajax_queue[key].length; i++) {
      if (_f4u$t.ajax_queue[key][i].time < t) {
        t = _f4u$t.ajax_queue[key][i].time;
        request = _f4u$t.ajax_queue[key][i].request;
        mykey = key;
      }
    }
    // always trim
    _f4u$t.ajax_queue[key] = _f4u$t.ajax_queue[key].slice(0,Math.min(5,_f4u$t.ajax_queue[key].length));
  }
  // trim first request off of successful array
  _f4u$t.ajax_queue[mykey] = _f4u$t.ajax_queue[mykey].slice(1,Math.min(5,_f4u$t.ajax_queue[key].length));
  return request;
}

// We update the user interface by polling the server every 40 ms
// But this is done only when no updates are pending for the server
_f4u$t.main_loop = function() {
  if ((_f4u$t.ajax_queue_length() > 0) || _f4u$t.ajax_queue_busy) {
    // we have pending updates to send to the server
    //_f4u$t.ajax_queue_busy = true;
    var request = _f4u$t.ajax_queue_get_request_and_trim();
    $.get(request)
      .done(function () {
        //console.log("request succeeded", request);
        _f4u$t.main_loop();
      })
      .fail(function () {
        console.log("request failed", request);
        _f4u$t.main_loop();
      });/*
      .always(function () {
        console.log("request passed", request);
      });*/
  } else {
    // regular polling
    _f4u$t.ajax_queue_busy = false;
    $.get(_f4u$t.ROOT, function(data) { _f4u$t.dispatch( data ); } );
    setTimeout ( function() { _f4u$t.main_loop(); }, 40);
  }		
}

$(document).ready(function() { _f4u$t.main_loop(); });
