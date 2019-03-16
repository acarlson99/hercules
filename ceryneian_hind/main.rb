#! /usr/bin/env ruby

require 'oauth2'

UID = # REDACTED
SECRET = # REDACTED

def findBoy(boy, token)
  status = 0
  begin
    while status != 200
      s = "v2/users/" + boy + "/locations"
      response = token.get s
      status = response.status
    end
    b = response.parsed[0]
    if not b['end_at']
      return b['host']
    else
      return "OFFLINE"
    end
  end
rescue
  return "USER DOES NOT EXIST"
end

def main(argv)
  begin
    client = OAuth2::Client.new UID, SECRET, site: "https://api.intra.42.fr"
    token = client.client_credentials.get_token
    begin
      File.foreach(argv[0]).with_index do |line, line_num|
        boy = line[0..-2]
        puts "#{line_num}: #{boy} #{findBoy boy, token}"
      end
    end
  rescue
    puts "FILE NOT FOUND ASSHOLE"
    exit 1
  end
rescue
  puts "Token could not be created"
  exit 1
end

if $PROGRAM_NAME == __FILE__
  if ARGV.length != 1
    puts "usage: ./main.rb boys.txt"
    exit 1
  end
  main(ARGV)
end
