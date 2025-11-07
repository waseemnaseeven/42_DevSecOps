# TOKENIZER

Here i'll explain all the choices i've made for this project.

deployment/ = “Here is my token and how i putted in the Ethereum blockchain” ✅
documentation/ = “Here is my token and here is how you can use it” ✅

## Blockchain 

Ethereum[https://ethereum.org/en/] : it's one of the most use blockchain for token creation, it's stable and secure creation. 

## Creation of the token 

- Solidity with openzeppelin[https://wizard.openzeppelin.com/] : It helps me create the smart contract with some functions on it. 
- Sepolia testnet[https://chainid.network/] : I used the sepolia test network, i needed to link my wallet with.
- Metamask : I use Metamask to have an Ethereum wallet. It gives me the ability to interact with the Ethereum blockchain by signing transactions through the app.
- Alchemy Faucet[https://www.alchemy.com/faucets/ethereum-sepolia] : I need faucet to have some test fees, since 2024-2025, its mandatory to have at least 0,0001 ETH 
- Remix[https://remix.ethereum.org/#lang=en&optimize=false&runs=200&evmVersion=null&version=soljson-v0.8.30+commit.73712a01.js] : It helps you compile the smartcontract and deployed it on a blockchain.

## Token feature

- Burnable: Allow token holders to burn their tokens.
- Mintable: Allow token owner to mint new tokens.
- ERC-20 I chose the ERC-20 standard because it's the most appropriate for token creation on Ethereum.
It's also compatible with most of the wallets, exchanges and smart contracts.

## Address of the token

- Etherscan[https://sepolia.etherscan.io/address/0x7B072eFD07fbCa0f7C3fEc50c015EBC78212e2a7] : here is my token[https://sepolia.etherscan.io/address/0xaf276dbbac46327d537088fda375503efbd65af7#code] the proof that in this address i've done token creation 
- Address of the contract we can interact with : `0xAf276dbBAC46327d537088FDa375503efbd65AF7`

## Security

- Ownable : some functions strictly for the owner
- Usage of OpenZeppelin to limit risks 
