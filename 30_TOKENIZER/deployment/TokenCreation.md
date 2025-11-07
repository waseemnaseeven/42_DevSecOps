## Token Creation

1. Creation of meta mask wallet
2. Usage of Solidity Smart Contracts on Openzeppelin
    - Here i can choose the protocol (ERC20) and the features functions for the smart contract
    - I chose : 
        - Burnable so that i can detroy tokens
        - Ownable so that it has proprietaire
        - ERC20Permit supports signature off-chains
        - Mintable by the owner
        - Pausable by the owner

3. Usage of Remix to compile my smart contract
    - It compiles the smart contract, transforming Solidity code into bytecode + ABI (Application Binary Interface)
    - Also generates a metadata.json file with : Compiler version, Source code hash, Dependencies (imports), Optimization flags.
    - Flattened the solidity code 

4. Before deploying, link my meta mask wallet with Sepolia test network
    - I needed to know the chain-id of the sepolia test network

5. Adding at least 0,0001 ETH to have Faucets, test fees (frais transactions) for sepolia testnet
    - I've used Alchemy

6. Deploying my token thanks to remix
    - Deploying a contract = sending a transaction.
    - MetaMask pops up:
        - From → your Ethereum account.
        - To → no address (since im creating a contract).
        - Data → the contract bytecode + constructor arguments.
        - Gas → estimated cost to run deployment.
        - I should must sign the transaction (proves i am the account owner).
    - Transaction broadcast:
        - After i sign, MetaMask sends the transaction to the Sepolia network via my connected provider (directly via MetaMask)
        - The transaction is added to the mempool, waiting for validators.
    - Block inclusion & contract creation
        - A validator includes your transaction in the next block.
        - The Ethereum Virtual Machine (EVM) executes the bytecode → this creates a new contract account with:
        - A unique contract address (calculated from your account + transaction nonce).
        - The bytecode stored permanently on-chain.
    - Updates 
        - We can now see all the public/external functions from the ABI (buttons like mint, burn, transfer).
        - Clicking these buttons creates new transactions (if state-changing) or simple calls (if read-only).

7. Verify and Publish: 
    - When i'm deploying my contract on Remix, blockchain store only bytecode, nobody can know whats my contract does without source code.
    - Verify and publish is associated source code with the bytecode on the blockchain, and show transparency.

Token: Wnaseeve42
Symbol: W42
Decimals: 18
Network: Ethereum Sepolia Testnet
Contract address: 0x7B072eFD07fbCa0f7C3fEc50c015EBC78212e2a7



