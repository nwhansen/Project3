<?php
//Error Reporting enable
error_reporting(E_ALL);
if (!ini_get('display_errors')) {
    ini_set('display_errors', 1);
}
ini_set('user_agent','cs3505_NullPointerExceptionBot');
if(!isset($_GET["url"]) || $_GET["url"] == "") {
	echo json_encode(array ( "Error"=> "No URL", "IsSet" => isset($_POST["url"])));
	return;
}
$url = $_GET["url"];
include "simple_html_dom.php";
//validate the url first. Absolute only
if(!isValidURL($url)){
	//die("ERROR: Invalid URL<form action=\"./\" method=post>url:<input type=text name=url value=\"$url\" /></form>");
	echo json_encode(array("Error" => "Invalid URL", "URL"=> $url));
	return;
}
//So we have a valid "url" lets try to get the header and make sure we don't get a 404
$response = get_headers($url, 1);
if($response[0] === NULL) {
	//Couldn't find the server
	echo json_encode(array("Error" => "Unable to locate server"));
	return;
}
if(strpos($response[0],"404") !== false ){ 
	//die("Error: "  . $response[0]);
	echo json_encode(array("Error" => $response[0]));
	return;
} 
//Lets do the processing
$htmlDoc = file_get_html($url);
if(!$htmlDoc){
	echo json_encode(array("Error" => "Unable to download file."));
	return;
}
$OutputArr = array();
//Yo dog i heard you like arrays!
$iMain = 0;
$i = 0;
//Images 
{
	$imageCount = 0;
	foreach($htmlDoc->find('img') as $element) 
			$imageCount++;
	//Add to output Arr
	$OutputArr ["images"] = $imageCount;
}
//Links
{
	$i = 0;
	$linksArray = array();
	foreach($htmlDoc->find('a') as $element) {
		if($element->href === false)
			continue;
		$linksArray [$i++] = $element->href;
	}
	//Add to output Arr
	//searchtag - Nathan H - enable prior to use. To much excess text for testing.
	$OutputArr["links"] = $linksArray ;
}
//The text.
{
	//Subtle problem, json only sends utf8-encoding therefor we must assure that pages like amazon don't try to screw with us.
	//searchtag - Nathan H - enable prior to use. To much excess text for testing.
	$OutputArr["rawText"] = utf8_encode($htmlDoc->plaintext);
}

//Begin amazon specific searching. Determine if we have a page that the reviews can be scraped.
{
	//We will assume that all amazon pages must be in the format of http://amazon.com or http://www.amazon.com maybe amazon.co.uk maybe.
	$OutputArr["isAmazon"] = (bool)preg_match("^http(s)?://(www.)?amazon\.(com|co\.uk)(/)?^",$url);
	if($OutputArr["isAmazon"]) {
		//Check to see if we have /review/ for a permalink to a review.
		$OutputArr["isReview"] = (bool)preg_match("^http(s)?://(www.)?amazon\.(com|co\.uk)/review/.*^",$url);
		$OutputArr["isProduct"] = (bool)preg_match("^http(s)?://(www.)?amazon\.(com|co\.uk)/(.*)/dp/.*^",$url);
		//Do the processing now!
		//If we are not on an isReview page then we can find the reviews by searching for the id "customerReviews" which is the container for the reviews
		if($OutputArr["isReview"]) {
			//Code logic parsing of name and link and description.
			//searchtag - Nathan H - Uncomment to get full output commented to clean output
			$OutputArr["ReviewDescription"] = $htmlDoc->find(".description",0)->plaintext;
			$OutputArr["ReviewerName"] = $htmlDoc->find(".reviewer", 0)->find("a",0)->plaintext;
			$OutputArr["ProductReviewed"] = $htmlDoc->find(".item",0)->find("a",0)->getAttribute("href");
		} else {
			//this is pretty much a product page.
		}
		
	}
	

}

echo json_encode($OutputArr);

//IsValid Provided by "sandykadam" located at the url: http://phpcentral.com/208-url-validation-in-php.html
//modifiyed to remove :port
function isValidURL($url) {
//return true;
 return preg_match('|^http(s)?://[a-z0-9-]+(.[a-z0-9-]+)*(/.*)?$|', $url);
 //|^http(s)?://[a-z0-9-]+(.[a-z0-9-]+)*(/.*)?$|i
}


?>

