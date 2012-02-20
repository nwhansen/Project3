#include "html_helper_tests.h"
#include "../html_helpers.h"

#ifdef VS
#define strcasecmp _stricmp
#endif

bool getFullURLTests()
{
	bool passed = true;

	passed = (strcasecmp(html_helpers::getFullURL("http://www.google.com", "doesn't matter").c_str(), "http://www.google.com") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("gmail", "http://google.com/").c_str(), "http://google.com/gmail") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("gmail", "http://google.com").c_str(), "http://google.com/gmail") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("gmail", "http://www.google.com").c_str(), "http://www.google.com/gmail") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("/gmail", "http://google.com").c_str(), "http://google.com/gmail") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("/gmail", "http://google.com/several/pages/deep.php").c_str(), "http://google.com/gmail") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("../gmail", "http://www.google.com/docs?brad=sucks").c_str(), "http://www.google.com/docs/../gmail") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("../gmail", "http://google.com/docs/index.php?brad=sucks").c_str(), "http://google.com/docs/../gmail") == 0) && passed;
	passed = (strcasecmp(html_helpers::getFullURL("../gmail", "http://google.com/docs/").c_str(), "http://google.com/docs/../gmail") == 0) && passed;

	return passed;
}

bool isValidURLTests()
{
	bool passed = true;

	passed = html_helpers::isValidURL("http://www.google.com") && passed;
	passed = html_helpers::isValidURL("https://www.google.com") && passed;
	passed = html_helpers::isValidURL("www.google.com") && passed;
	passed = html_helpers::isValidURL("www.google.com/") && passed;
	passed = html_helpers::isValidURL("www.google.com/?brad=sucks") && passed;
	passed = html_helpers::isValidURL("www.google.com/brad/sucks") && passed;
	passed = html_helpers::isValidURL("www.google.com/brad/sucks?really=yes") && passed;
	passed = html_helpers::isValidURL("http://atr.eng.utah.edu/~eolson/cs4540/ps3/index.php/?urlsdlkj=sgjsrg?/fjjhfgjh&euyr=dkjf") && passed;
	passed = !html_helpers::isValidURL("http://atr.eng.utah.edu/~eolson/cs4540/ps3/index.edo?urlsdlkj=sgjsrg?/fjjhfgjh&euyr=dkjf") && passed;
	passed = html_helpers::isValidURL("sucks.fail") && passed;
	passed = !html_helpers::isValidURL("www.google.com/sucks.fail") && passed;

	return passed;
}

bool isWithinDomainTests()
{
	bool passed = true;

	passed = html_helpers::isWithinDomain("google.com", "google.com") && passed;
	passed = html_helpers::isWithinDomain("http://google.com", "http://google.com") && passed;
	passed = html_helpers::isWithinDomain("http://google.com/gmail/inbox", "http://google.com/") && passed;
	passed = html_helpers::isWithinDomain("http://subdomain.google.com", "http://subdomain.google.com") && passed;
	passed = html_helpers::isWithinDomain("http://subdomain.google.com", "http://google.com") && passed;
	passed = !html_helpers::isWithinDomain("http://google.com", "http://subdomain.google.com") && passed;
	passed = html_helpers::isWithinDomain("http://subsub.subdomain.google.com", "http://subdomain.google.com") && passed;
	passed = !html_helpers::isWithinDomain("http://subdomain.google.com", "http://subsub.subdomain.google.com") && passed;

	return passed;
}

bool stripHashTagsTest()
{
	bool passed = true;

	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com").c_str(), "http://www.google.com") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com/").c_str(), "http://www.google.com/") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com/test#test").c_str(), "http://www.google.com/test") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com#test").c_str(), "http://www.google.com") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com/test?brad=sucks").c_str(), "http://www.google.com/test?brad=sucks") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com/test#removeAll?brad=sucks").c_str(), "http://www.google.com/test") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com/test?brad=sucks#removeAll").c_str(), "http://www.google.com/test?brad=sucks") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("http://www.google.com#test?brad=sucks#removeAll").c_str(), "http://www.google.com") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("#").c_str(), "") == 0) && passed;
	passed = (strcasecmp(html_helpers::stripHashTag("#test").c_str(), "") == 0) && passed;

	return passed;
}

bool runAllHTMLHelperTests()
{
	bool returnVal = true;

	if (!getFullURLTests())
	{
		printf("getFullURLTests failed\n");

		returnVal = false;
	}

	if (!isValidURLTests())
	{
		printf("isValidURLTests failed\n");

		returnVal = false;
	}

	if (!isWithinDomainTests())
	{
		printf("isWithinDomainTests failed\n");

		returnVal = false;
	}

	if (!stripHashTagsTest())
	{
		printf("stripHashTagsTest failed\n");

		returnVal = false;
	}

	return returnVal;
}
