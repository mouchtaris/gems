require 'util/lazy_block'

RSpec.describe Util::LazyBlock do
  def make_block_spy
    instance_double(Proc).tap do |spy|
      allow(spy).to receive :call
    end
  end

  let(:block_spy) { make_block_spy }
  let(:call_block_spy) { make_block_spy }
  let(:cargs) { Array.new(3) { Object.new } }
  let(:copts) { Hash[one: :two, three: 4] }
  let(:largs) { Array.new(3) { Object.new } }
  let(:lopts) { Hash[five: :six, seven: 'ate nine'] }
  let(:cblock) { Proc.new{} }
  let(:call_block) { proc { |*a, **o, &b| call_block_spy.call(*a, **o, &b) } }
  let(:total_args) { cargs + largs }
  let(:total_opts) { copts.merge(lopts) }

  describe 'no construction opts, block' do
    let(:lblock) { described_class.new(block_spy, *cargs) }

    before do
      lblock.call(*largs)
    end

    it 'passes construction and call args in order' do
      expect(block_spy).to have_received(:call).with(*total_args)
    end
  end

  describe 'constructions opts, no block' do
    let(:lblock) { described_class.new(block_spy, *cargs, **copts) }

    before do
      lblock.call(*largs, **lopts)
    end

    it 'passes construction and call args and opts in order' do
      expect(block_spy).to have_received(:call).with(*total_args, **total_opts)
    end
  end

  describe 'passing blocks' do
    let(:lblock) { described_class.new(block_spy, *cargs, **copts, &cblock) }

    describe 'when only construction block given' do
      before do
        lblock.call()
      end

      it 'passes construction args and construction block if no block given' do
        expect(block_spy).to have_received(:call).with(*cargs, **copts, &cblock)
      end
    end

    describe 'when call block is given' do
      before do
        lblock.call(*largs, **lopts, &call_block)
      end

      it 'passes construction and call args and opts and block in order' do
        expect(block_spy).to have_received(:call).with(*total_args, **total_opts, &call_block)
      end
    end
  end
end
