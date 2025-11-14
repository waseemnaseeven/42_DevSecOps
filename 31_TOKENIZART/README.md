# TOKENIZART

Here i'll explain all the choice i've made for this project.

deployment/ = “Here is my token and how i putted in the Ethereum blockchain” ✅
documentation/ = “Here is my token and here is how you can use it” ✅
images/ = "my images for the NFT"
metadata/ = the metadata and all the informations about the NFT 

## Blockchain 

Ethereum[https://ethereum.org/en/] : it's one of the most use blockchain for token creation, it's stable and secure creation. 

## Creation of the NFT 

- Solidity with openzeppelin[https://wizard.openzeppelin.com/] : It helps me create the smart contract with some functions on it. 
- Sepolia testnet[https://chainid.network/] : I used the sepolia test network, i needed to link my wallet with.
- Metamask : I use Metamask to have an Ethereum wallet. It gives me the ability to interact with the Ethereum blockchain by signing transactions through the app.
- Alchemy Faucet[https://www.alchemy.com/faucets/ethereum-sepolia] : I need faucet to have some test fees, since 2024-2025, its mandatory to have at least 0,0001 ETH 
- Remix[https://remix.ethereum.org/#lang=en&optimize=false&runs=200&evmVersion=null&version=soljson-v0.8.30+commit.73712a01.js] : It helps you compile the smartcontract and deployed it on a blockchain.
- ipfs[https://ipfs.tech/] : Internet Planetary File System to retrieve address of folder.
- Pinata[https://pinata.cloud/] : Deploying my NFT on ipfs permanently.

## NFT feature

- Mintable: Allow token owner to mint new tokens.
- ERC-721 defines a standard for non-fungible tokens (NFTs), where each token is unique and has distinct characteristics. This uniqueness is crucial for representing ownership of specific assets like digital art, collectibles. Each ERC-721 token can carry individual metadata that may include attributes, ownership history, and other identifiers that distinguish one token from another.

## Address of the CyberNFT42 

- Etherscan[https://sepolia.etherscan.io/address/0xd652bbee509c1174f026de830cdad12c733146cf#code]
- The contract address to interact with : 0xD652BBEE509c1174f026de830cdaD12c733146cf