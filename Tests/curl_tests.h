/*
 * Submitted by:
 *   Nate Anderson
 *   Nathan Hansen
 *   Cody Foltz
 *   Eric Olson
 *
 * For Assignment #3, cs3505, January 2012
 */

#pragma once

size_t curl_easy_test1_callback(void *ptr, size_t numberOfElements, size_t bytesPerElement, void *userdata);
bool curl_easy_test1();

size_t curl_relative_path_test1_callback(void *ptr, size_t numberOfElements, size_t bytesPerElement, void *userdata);
bool curl_relative_path_test1();

size_t curl_amazon_product_page_test1_callback(void *ptr, size_t numberOfElements, size_t bytesPerElement, void *userdata);
bool curl_amazon_product_page_test1();
