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