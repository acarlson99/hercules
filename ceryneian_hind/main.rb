#! /usr/bin/env ruby

require 'oauth2'

UID = # NOT PUSHING THIS
SECRET = # NOT PUSHING THIS

def findBoy(token, boy)

end

def main()
  client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")
  token = client.client_credentials.get_token

  File.foreach("boys.txt").with_index do |line, line_num|
    puts "#{line_num}: #{line[0..-2]} #{findBoy(token, line)}"
  end
end

if $PROGRAM_NAME == __FILE__
  main()
end
