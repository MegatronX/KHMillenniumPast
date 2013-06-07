// global vars 
now = new Date();
random = now.getTime();

// construct UI properly
function cleanUI(uiParameter) {
	if (uiParameter!=null) {
		if (uiParameter.indexOf("ui=")!=0) {
			uiParameter = "ui=" + uiParameter;
	    }
	} else {
    	uiParameter='';
    }
return(uiParameter);
}

// popups that should be resized based on the user status
function popWindowSizeReg(regx,regy,anonx,anony) {
	if (checkRegistration()) {
		windowsize = "width="+regx+",height="+regy;
	} else {
		windowsize = "width="+anonx+",height="+anony;
	}
return windowsize;
}

// mediaviewer video popup windows
function popSizedWinProtected(url, name, type, width, height, locked){
// add 35 for wmv player controls
height=height+35;	
var hostname = window.location.hostname;
	if (locked == null) { locked = 1; }
	if ( (hostname.indexOf('gamespy') == -1) && (locked != 0) && (!checkSubscription()) ) {
		window.location.href="http://my.ign.com/my/sb?action=userauth&customMsg=userauthSubMedia4&network=1&category=subscription&RegPath=2&destination="+ urlEncode(window.location.href);
	} else {
		var thepopup = window.open(url, name ,'width=' + width + ',height=' + height + ',resizable=no,scrollbars=no');				
	}
}

// mediaviewer video popup windows - version 2
function popSizedWinProtected2(url, name, type, width, height, locked){
var hostname = window.location.hostname;
	if (locked == null) { locked = 1; }
	if ( (hostname.indexOf('gamespy') == -1) && (locked != 0) && (!checkSubscription()) ) {
		window.location.href="http://my.ign.com/my/sb?action=userauth&customMsg=userauthSubMedia4&network=1&category=subscription&RegPath=2&destination="+ urlEncode(window.location.href);
	} else {
		var thepopup = window.open(url, name ,'width=' + width + ',height=' + height + ',resizable=no,scrollbars=no');				
	}
}

// alert for right-clicking locked files in video gallery pages
function clickCheck() {
if (!checkSubscription()) {
alert('You must be logged in as an IGN Insider to access this content.')
}
}

// allows section controllers to check parameters passed in URL strings 
function checkParam(param,value) {
p = new String(document.location);
p = p.substring( p.indexOf('?')+1 , p.length );
var compareField = new String(param);
if (p.indexOf(compareField) > -1) { 
	var compareValue = new String(value);
	pArray = p.split("&");
	k = pArray.length;
	for (i= 0 ; i < k; i++) {
		keyVal = pArray[i].split('=');
		if (keyVal.length != 2) { 
			continue; 
		}
		if (keyVal[0] == compareField && keyVal[1] == compareValue) { 
			return true; 
		}
	}
 }
return false;
}

function getParm( name ) //used to get the value of URL parameters
{
  name = name.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");
  var regexS = "[\\?&]"+name+"=([^&#]*)";
  var regex = new RegExp( regexS );
  var results = regex.exec( window.location.href );
  if( results == null )
    return "";
  else
    return results[1];
}


function stf( url ) {
	var u = top.document.location;
    if ( url ) {
        u = url;
    }
	var stfurl = "http://www.ign.com/stf/index.html?pst=1&url=" + u;
	var newWindow = window.open(stfurl,"","status,height=500,width=450");
}
function stf_spy( url ) {
	var u = top.document.location;
    if ( url ) {
        u = url;
    }
	var stfurl = "http://www.gamespy.com/stf/index.html?pst=1&url=" + u;
	var newWindow = window.open(stfurl,"","status,height=500,width=450");
}
function goLogin() {
	windowgoto = "http://my.ign.com/my/sb?paction=relogin&params=" + urlEncode("#action#protect#location#" + urlEncode(window.location));
	// var newWindow = window.open(windowgoto,'','');
	document.location = windowgoto;
return false;
}

// handy urlEncoder -- used by regprotect
function urlEncode(inStr) {
	inStr = new String(inStr);
	outStr=' '; //not '' for a NS bug!
	for (i=0; i < inStr.length; i++) {
		aChar=inStr.substring (i, i+1);
		switch(aChar){
case '%': outStr += "%25"; break; case ',': outStr += "%2C"; break;
case '/': outStr += "%2F"; break; case ':': outStr += "%3A"; break;
case '~': outStr += "%7E"; break; case '!': outStr += "%21"; break;
case '"': outStr += "%22"; break; case '#': outStr += "%23"; break;
case '$': outStr += "%24"; break; case "'": outStr += "%27"; break;
case '`': outStr += "%60"; break; case '^': outStr += "%5E"; break;
case '&': outStr += "%26"; break; case '(': outStr += "%28"; break;
case ')': outStr += "%29"; break; case '+': outStr += "%2B"; break;
case '{': outStr += "%7B"; break; case '|': outStr += "%7C"; break;
case '}': outStr += "%7D"; break; case ';': outStr += "%3B"; break;
case '<': outStr += "%3C"; break; case '=': outStr += "%3D"; break;
case '>': outStr += "%3E"; break; case '?': outStr += "%3F"; break;
case '[': outStr += "%5B"; break; case '\\': outStr += "%5C"; break;
case ']': outStr += "%5D"; break; case ' ': outStr += "+"; break;
default: outStr += aChar;
		}
}
return outStr.substring(1, outStr.length);
}

// Replaces text with by in string
function js_replace(s,text,by) { 
    var sLength = s.length;
    var txtLength = text.length;
    if ((sLength == 0) || (txtLength == 0)) return s;
    var i = s.indexOf(text);
    if ((!i) && (text != s.substring(0,txtLength))) return s;
    if (i == -1) return s;
    var newstr = s.substring(0,i) + by;
    if (i+txtLength < sLength) {
        newstr += js_replace(s.substring(i+txtLength,sLength),text,by);
    }
    return newstr;
}

// onclick linktracker that usees ata
function trackclick(aid,agg) {
	var now      = new Date();
	var random   = now.getTime();
	var ref 	 = "&r=" + escape(document.location);
		ref      = ref.split('/').join('%2F');
		ref      = ref.split('.').join('%2E');
		ref      = ref.split('%').join('$');		
	var origin = document.location.toString().substring(7); /* convert location to string, trim http:// */
		origin = origin.substring(0,origin.indexOf('/')); /* pull subdomain only */
		aid = aid + "-" + origin;
	var lnk      = "&p=http://www.ignlinktrack.com/" + aid;
		lnk      = lnk.split('/').join('%2F');
		lnk      = lnk.split('.').join('%2E');
		lnk      = lnk.split('%').join('$');
	var pt = "&pagetype=";
		ptstring = ataxscript.substr(ataxscript.indexOf('pagetype=')+9);
		pt = pt + ptstring.substr(0,ptstring.indexOf('&'));		
	var aggval = ""; if (agg!=null) aggval = "&aggregate="+agg;
        i = new Image();
        i.src  = "http://atax.ign.com/network=ign&size=1x1" + lnk + ref + pt + aggval + "&name=ATAtracker?"+ random + "\" height=\"1\" width=\"1\" style=\"position: absolute; visibility: hidden";
}

function trackclickSwf(aid,url) {
	trackclick(aid);
	document.location = url;
}

function gspy_trackclick(aid) {
	var now      = new Date();
	var random   = now.getTime();
	var ref 	 = "&r=" + escape(document.location);
		ref      = ref.split('/').join('%2F');
		ref      = ref.split('.').join('%2E');
		ref      = ref.split('%').join('$');		
	var origin = document.location.toString().substring(7); /* convert location to string, trim http:// */
		origin = origin.substring(0,origin.indexOf('/')); /* pull subdomain only */
		aid = aid + "-" + origin;
	var lnk      = "&p=http://www.ignlinktrack.com/" + aid;
		lnk      = lnk.split('/').join('%2F');
		lnk      = lnk.split('.').join('%2E');
		lnk      = lnk.split('%').join('$');
        i = new Image();
        i.src  = "http://atax.gamespy.com/network=gamespy&size=1x1" + lnk + ref + "&name=ATAtracker?"+ random + "\" height=\"1\" width=\"1\" style=\"position: absolute; visibility: hidden";
}
// trim function, removes spacing. Function 1 of 2
function s_trim(TRIM_VALUE) {
	if(TRIM_VALUE.length < 1) return"";
    TRIM_VALUE = StringTrim(TRIM_VALUE,'right');
    TRIM_VALUE = StringTrim(TRIM_VALUE,'left');
    if(TRIM_VALUE=="") return "";
		else return TRIM_VALUE;
}

// trim function, removes spacing from a specific side. Function 2 of 2
function StringTrim(VALUE,SIDE) {
	var v_length = VALUE.length;        
	if(v_length < 0) return "";
	var s = SIDE; 
	var w_space = String.fromCharCode(32);
	var strTemp = "";
	if (s == 'right') { // right side
		var iTemp = v_length -1;
		while(iTemp > -1){
			if(VALUE.charAt(iTemp) == w_space){}
	        else {
	        	strTemp = VALUE.substring(0,iTemp +1);
	          	break;
			}
	        iTemp = iTemp-1;
		}
	} else { // left side
		var iTemp = 0;
	    while(iTemp < v_length){
	    	if(VALUE.charAt(iTemp) == w_space){}
	        else{
	        	strTemp = VALUE.substring(iTemp,v_length);
	            break;
	        }
			iTemp = iTemp + 1;
		}
	}
return strTemp;
}

// check to see if this is a UK domain
function checkUK() {
	p = new String(document.location);
	if ( (p.substring(0,10) == "http://uk.") || (checkParam('isUKtest','true')) ) { 
		return true;
	}
return false;
}

// checks to see if the parameter matches the current locale or if a setLocale parameter was passed in the url
function  checkLocale(LOCALE){
		urlLocale = getLocale();
		paramLocale = LOCALE;
		
	if (urlLocale == paramLocale){
		return true;
	}
	if (checkParam('setLocale',paramLocale)){
		return true;
	}
 return false;

}

//gets the locale by using a regular expression to grab whatever is between the first '//' and the first '.' in the url
function getLocale(){
  p = new String(document.location);
  regx = /\/\/(\w.*?)\./;
  result = p.match(regx);
	if ( result != null ) { 
		return result[1];
	}
}

// allows a search with radio buttons. this function is IGN specific, other network includes have diff site values
function multiSiteSearchSubmit(form) { 
	var subdomain = document.location.href;
	qry = urlEncode(form.query.value);
	if (qry=="") { alert('Please type in your search query.'); return; } // check for empty strings 
	redir = "";
	if (form.domain[0].checked) { // assumes global WebSearch is listed first
		redir = "http://search.ign.com/web?query=" + qry;
	} else if (form.domain[1].checked) { // assumes site search is second
		redir = "http://search.ign.com/products?query=" + qry;
	} else { 
		if (subdomain.match(/boards\.ign\.com/)) { // assumes board search is third
		redir = "http://boards.ign.com/ASP/search_boards.asp?search_phrase=" + qry;
		} else {
		    var objtName = form.objtName.value;
			searchTerm="http://search.ign.com/products?genNav=true&query=";
		    additionalSearchTerm = "&objtName=" +objtName;
		    if (objtName == 'game' ) { additionalSearchTerm = "&platformSearch=" +form.platformSearch.value; }
			if (objtName == 'article' ) { searchTerm = "http://search.ign.com/articles?genNav=true&typeName=" + form.typeName.value + "&query=" ; }
			redir= searchTerm + qry + additionalSearchTerm;
		}
				
	}
	gotoval = redir;
	if (gotoval != "") { document.location=gotoval; }
	return;
}
	
function showSummary(a,b) { //min & max posts
	var longSummary = document.getElementById(a); // object to be hidden
	var shortSummary = document.getElementById(b); // object to be shown
	
	if(longSummary.style.display != 'none') {	
		longSummary.style.display = 'none';
		shortSummary.style.display = '';
	} else if(shortSummary.style.display != 'none') { 
		longSummary.style.display = '';
		shortSummary.style.display = 'none';
	}
}	

// image loader
document.write("<scr"+"ipt type='text/javascript' SRC='http://scripts.ign.com/scripts/ign/utilities.js'></scr"+"ipt>");	
function onBodyLoad() {
}

// used for old section alphy display, here so we can deprecate tmp_sections.js
function letterStyleOn(letterId) {
	var letterElement = document.getElementById(letterId);
	letterElement.style.backgroundColor = "#adadad";
	letterElement.style.color = "#fff";	
}

//contents of json_functions_lib.js & jsr.js
// JSONscriptRequest -- a simple class for making HTTP requests
// using dynamically generated script tags and JSON
//
// Author: Jason Levitt
// Date: December 7th, 2005

function JSONscriptRequest(fullUrl) {
    // REST request path
    this.fullUrl = fullUrl; 
    // Keep IE from caching requests
    this.noCacheIE = '&noCacheIE=' + (new Date()).getTime();
    // Get the DOM location to put the script tag
    this.headLoc = document.getElementsByTagName("head").item(0);
    // Generate a unique script tag id
    this.scriptId = 'YJscriptId' + JSONscriptRequest.scriptCounter++;
}
// Static script ID counter
JSONscriptRequest.scriptCounter = 1;
// buildScriptTag method
//
JSONscriptRequest.prototype.buildScriptTag = function () {
    // Create the script tag
    this.scriptObj = document.createElement("script");
    // Add script object attributes
    this.scriptObj.setAttribute("type", "text/javascript");
    this.scriptObj.setAttribute("src", this.fullUrl + this.noCacheIE);
    this.scriptObj.setAttribute("id", this.scriptId);
}
// removeScriptTag method
// 
JSONscriptRequest.prototype.removeScriptTag = function () {
    // Destroy the script tag
    this.headLoc.removeChild(this.scriptObj);  
}
// addScriptTag method
//
JSONscriptRequest.prototype.addScriptTag = function () {
    // Create the script tag
    this.headLoc.appendChild(this.scriptObj);
}

function getSubmittedData(url) {
	// Create a new script object
      aObj = new JSONscriptRequest(url);
      // Build the script tag
      aObj.buildScriptTag();
      // Execute (add) the script tag
      aObj.addScriptTag();
    }
