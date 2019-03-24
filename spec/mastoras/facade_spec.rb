# frozen_string_literal: true

require 'spec_helper'

require 'mastoras/facade'

RSpec.describe Mastoras::Facade do
  let(:samples) { Pathname.new(__dir__) / '..' / '..' / '_sample' }
  let(:sample_good) { samples / 'good' / 'mastrofile' }
  let(:facade) { described_class.new sample_good }
  it 'exists' do
  end

  describe '#initialize' do
    describe 'with good mastroroot' do
      subject { facade }
      it 'gets constructed' do
        expect { subject }.not_to raise_error
      end

      describe '#ws (workspace)' do
        describe '#config' do
          subject { facade.ws.config }
          it { is_expected.to be_a Hash }
        end
        describe '#library' do
          subject { facade.ws.library }
          it { is_expected.to be_a Pathname }
          it 'is a child of mastroroot' do
            expect(sample_good.dirname.children).to include subject
          end
          describe '#basename' do
            subject { facade.ws.library.basename.to_s }
            it { is_expected.to eq 'mastrorepo' }
          end
        end
        describe '#bazaar' do
          subject { facade.ws.bazaar.basename.to_s }
          it { is_expected.to eq '_artifacts' }
        end
        describe '#scrolls.name' do
          subject { facade.ws.scrolls.map(&:name).to_a }
          describe 'values' do
            it 'includes arch_base' do
              is_expected.to include 'arch_base'
            end
            it 'includes arch_updated' do
              is_expected.to include 'arch_updated'
            end

            describe '.arch_base' do
              let(:scroll) { facade.ws.scroll_of 'arch_base' }
              describe '#builder_types' do
                subject(:builder_types) { scroll.builder_types.to_a }
                it { is_expected.to include 'vagrant' }
                describe '#size' do
                  subject(:size) { builder_types.size }
                  it { is_expected.to be 1 }
                end
              end
            end
          end
        end
      end
    end

    describe 'with wrong arguments' do
      subject { described_class.new sample_good.to_s }
      it 'does not accept non-Pathname root' do
        expect { subject }.to raise_error ArgumentError
      end
    end
  end
end
