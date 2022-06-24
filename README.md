## Commitment Scheme/Betting

### Purpose
This program implements the cryptographic primitive of a Commitment Scheme, as referenced in Chapter 1 of Narayanan et al.'s "Bitcoin and Cryptocurrency Technologies". Provides a "secure" service through which a user can commit to a message or bet (string) such that the message can't be tampered with when displaying it (verifying).

### Disclaimer
This program should not be used to contain any sensitive information -- my implementations of these algorithms may not be complete, and no degree of security is gauranteed. When dealing with any privacy or security-related task, make sure to use the industry standard. This program was created simply to understand the basics of how these systems work.

### Usage
A user commits to a message using the Bet::commit() function, which generates both a 'Promise' and a 'Bet Access Key'. Keep track of these two strings. This action is equivalent to putting a sealed envelope on a table without revealing what's in the envelope. When ready to open the envelope and display the contents, use the Bet::verify() function. This takes in as input the Promise and Bet Access Key, and asks the person who committed the message exactly what they committed to (displaying the message). The program will then display if this is indeed what the person committed to or not, and prevents the message they committed to from being tampered.

For example, if someone agreed to bet on a team losing by x, and they instead lost by y, this program will make it 'impossible' to tamper with the message in the sealed envelope to change it to the team losing by y. 

### Under the Hood
To make this work, the commitment scheme is implemented using a home-made hash function. This hash-function attempts to be one-way collision-resistant and close to a cryptographic hash function. To accomplish this, the Merkle-Damgard construction for arbtirary length inputs is implemented, along with a Davies-Meyer encryption handler and an Autokey Cipher in place of the encryption. The commitment scheme also uses 'salting' to help ensure security by generating a nonce, inherent to how a commitment scheme works.
