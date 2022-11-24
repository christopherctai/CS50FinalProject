# Notes from Flask tutorials 

# Using Engine X and 

"""
deploy to a virtual machine hosted by a company 

Like Linode, digital ocean, or aws etc. Going to use Linode 

Using own domain name - need to upgrade to a paid service on free options to set it up. 
In this video, it'll use more freedom but it's not as simple as other methods 

You can do the same deployment with any linux server

Create an account 

Saving the ssh IP address: 173.230.149.222

Paste the ssh command into your linux terminal to open a new command line
This opens a new server! 

Log in as a limited user, NOT as the root because that's kinda dangerous. So we make a new user and we give them sudo privileges 

Set up SSH key authentication. By default we use a password to get into our server, but we instead want to use key based authentication. 
This is better. Uses keys that are better and you don't have to use your password every time. 

Setting the permissions for the SSH directory so the ownder has read/write permission, and the owner of the files can read and write the files 
The first digit in like 700 or 600 is for the owner of the file. 7 means read write and execute. the 0 means for the group, and the other 0 means for everyone else 
Same with the 6 and 0 and 0! 
Should now be able to log in without a password, and instead use public/private ssh keys 

Disallow root logins over SSH
Change values in a config file 
Now if a hacker tries to log in through root, they cannot 
Turning password authentication to no. Since we have ssh keys, we don't need to use passwords. 

Then restart the ssh service with: sudo systemctl restart ssh

Configuring allow rules 
for ceertain ports. usin ga default deny would log you out of the server unless ou use the best rules possible 
For instance, allow port 5000 
don't allow other stuff until it's working the way we want it to 

Now we want to deploy this thing! If it's checked into a git repo we can git clone into our server
"""