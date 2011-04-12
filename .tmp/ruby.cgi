#!/usr/bin/ruby
# ruby.cgi

require 'cgi'

# Create a cgi object, with HTML 4 generation methods.
cgi = CGI.new('html4')

values_list = ""

cgi.params.each_pair do |k,d|
  values_list += '<li>'+k+' = '+d.join(',')+'</li>'
end

# Ask the cgi object to send some text out to the browser.
cgi.out {
 cgi.html {
   cgi.body {
     cgi.h1 { 'You send:' } +
     cgi.ul {
       values_list
     }
   }
 }
}
