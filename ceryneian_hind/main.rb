#! /usr/bin/env ruby

require 'oauth2'

UID = ENV['ceryneian_hind_UID']
SECRET = ENV['ceryneian_hind_SECRET']

def findBoy(boy, token)
  s = "v2/users/" + boy + "/locations"
  begin
    response = token.get s
    while response.status != 200
      puts "No response... Trying again"
      sleep 5
      response = token.get s
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
    puts "Error making request"
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
  if not UID or not SECRET
    puts "Bruh set UID and SECRET"
    exit 1
  end
  main(ARGV)
end
